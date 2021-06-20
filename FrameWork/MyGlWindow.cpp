#include "MyGlWindow.h"
#include "WindEffect.h"

#include <fstream>
#include <iostream>
#include "drawUtils.h"
#include "timing.h"

static double DEFAULT_VIEW_POINT[3] = { 53, 77.951, 74.6012 };
static double DEFAULT_VIEW_CENTER[3] = { 53, -20.46, -17.7185 };
static double DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };

#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)
#define DEPTH 20
#define NB_POINTS 1000
#define SPACE 10
#define MIN_FLOOR_Y 10
#define MAX_FLOOR_Y 60
#define START_VALUE 35
#define MAX_DELTA 8
#define CHUNK_SIZE 500 / SPACE
#define LEFT_POSITION -150
#define SLINGSHOT_STRENGHT 25

void drawStrokeText(const char* string, int x, int y, int z)
{
	const char* c;
	glPushMatrix();
	glTranslatef(x, y + 8, z);
	glScalef(0.2, 0.2, 0.2);
	for (c = string; *c != '\0'; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}


void MyGlWindow::putText(const char* string, int x, int y, float r, float g, float b)
{
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ortho();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glColor3f(r, g, b);
	drawStrokeText(string, x, y, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void MyGlWindow::resetGame()
{
	game_step = 0;
	this->_score = 0;
	floor->regenerate(NB_POINTS, SPACE, MIN_FLOOR_Y, MAX_FLOOR_Y, START_VALUE, MAX_DELTA);
	floor->setPosition(cyclone::Vector3(LEFT_POSITION, 0, 0));
	floor->setLeftX(LEFT_POSITION);
	player->resetTranslation(cyclone::Vector3(0, START_VALUE + 19 + player->radius, 0));
	slingshot->setForce(new cyclone::MyAnchoredSpring(new cyclone::Vector3(0, START_VALUE + 20 + player->radius, 0), SLINGSHOT_STRENGHT, 0.0));
	m_objects[0].second = true;
}

MyGlWindow::~MyGlWindow()
{
	std::ofstream stream{ "highscore.dat", std::ifstream::binary };

	if (!stream.fail())
		stream.write(reinterpret_cast<char *>(&this->_highScore), sizeof(this->_highScore));
}

MyGlWindow::MyGlWindow(int x, int y, int w, int h) :
	Fl_Gl_Window(x, y, w, h)
	//==========================================================================
{
	std::ifstream stream{ "highscore.dat", std::ifstream::binary };

	if (!stream.fail())
		stream.read(reinterpret_cast<char *>(&this->_highScore), sizeof(this->_highScore));
	mode(FL_RGB | FL_ALPHA | FL_DOUBLE | FL_STENCIL);

	fieldOfView = 45;

	glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
	glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
	glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);

	float aspect = (w / (float)h);
	m_viewer = new Viewer(viewPoint, viewCenter, upVector, 45.0f, aspect);

	TimingData::init();
	run = 0;

	m_c_resolver = new MyCollisionResolver();

	launch_ball = [this](cyclone::Particle* contact) {
		if (game_step == 2) {
			game_step = 3;
			slingshot->setForce(NULL);
		}
	};

	setupForces();
	setupObjects();
	resetGame();
}

void MyGlWindow::setupForces() {
	m_world = new MyWorldSpec(cyclone::Vector3::GRAVITY);
	water = new MyLiquid((MAX_FLOOR_Y - MIN_FLOOR_Y) * 0.15, 5, m_world);
	water->setPosition(cyclone::Vector3(0, MIN_FLOOR_Y, 0));
	water->width = DEPTH*2 - 0.01;
	water->length = CHUNK_SIZE * SPACE;

}

void MyGlWindow::setupObjects() {
	player = new MySphere(3, 10, m_world);
	player->particle->setDamping(0.9);
	water->m_force->setTarget(player);

	floor_contact = new cyclone::MyLinesContact({});
	floor_contact->init(player->particle, player->radius);
	m_c_resolver->m_contacts.push_back(floor_contact);

	floor = new Floor(m_world, DEPTH, NB_POINTS, SPACE, MIN_FLOOR_Y, MAX_FLOOR_Y, START_VALUE, MAX_DELTA);
	floor->setChunkSize(CHUNK_SIZE);
	floor->setPosition(cyclone::Vector3(LEFT_POSITION, -15, 0));
	floor->setLeftX(LEFT_POSITION);
	floor->setBottom(-100);

	slingshot = new PoleConnection(player);
	slingshot->setForce(new cyclone::MyAnchoredSpring(new cyclone::Vector3(0, START_VALUE + 20 + player->radius, 0), SLINGSHOT_STRENGHT, 0.0));

	auto launch = new cyclone::MyCircleContact(cyclone::Vector3(0, START_VALUE + 20 + player->radius, 0), 3.0);
	launch->is_trigger = true;
	launch->init(player->particle, player->radius);
	launch->onEnter = &launch_ball;
	m_c_resolver->m_contacts.push_back(launch);

	m_objects.emplace_back(player, true);
	m_renderables.push_back(slingshot);
	m_renderables.push_back(floor);
	m_renderables.push_back(new WindEffect(*floor, 3.1415, { 0, 0 }, { 300, 300 }));
	m_objects.emplace_back(water, false);
}

void MyGlWindow::setupLight(float x, float y, float z)
{

	// set up the lighting
	GLfloat lightPosition[] = { 500, 900.0, 500, 1.0 };
	GLfloat lightPosition2[] = { 1, 0, 0, 0 };
	GLfloat lightPosition3[] = { 0, -1, 0, 0 };

	GLfloat violetLight[] = { 0.5f, 0.1f, .5f, 1.0 };
	GLfloat whiteLight[] = { 1, 1, 1, 1.0 };
	GLfloat whiteLight2[] = { .3, .3, .3, 1.0 };
	GLfloat blueLight[] = { .1f,.1f,.3f,1.0 };


	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_DEPTH);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);


	lightPosition[0] = x;
	lightPosition[1] = y;
	lightPosition[2] = z;

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, whiteLight2);
	// 
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, whiteLight);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MyGlWindow::drawStuff()
{
	polygonf(4, 20., 0., -25., 20., 0., 25., 20., 30., 25., 20., 30., -25.);
}

void MyGlWindow::drawScoreLine(float r, float g, float b, float score)
{
	glBegin(GL_LINES);
	glColor3f(r, g, b);
	glVertex2f(score, 0);
	glVertex2f(score, 100);
	glEnd();
}

//==========================================================================
void MyGlWindow::draw()
//==========================================================================
{
	glViewport(0, 0, w(), h());

	// clear the window, be sure to clear the Z-Buffer too
	glClearColor(0.2, 0.2, 0.7, 1);		// background should be blue

	focus_cam(player->particle);

	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);


	// now draw the ground plane
	setProjection();
	/*
		setupFloor();

		glPushMatrix();
		drawFloor(200, 20);
		glPopMatrix();
	*/

	setupLight(m_viewer->getViewPoint().x, m_viewer->getViewPoint().y, m_viewer->getViewPoint().z);

	/*
	//Draw axises
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 100, 0);

	glColor3f(0, 1, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(100, 0, 0);

	glColor3f(0, 0, 1);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100);
	glEnd();
	glLineWidth(1.0f);
	*/

	/////////////////////////
//	putText("7001539", 0, 0, 1, 1, 0); // ça nique le doPick()

	//draw shadow
	setupShadows();
	for (auto item : m_renderables)
	{
		item->draw(1);
	}
	for (auto item : m_objects)
	{
		item.first->draw(1);
	}
	unsetupShadows();

	for (auto item : m_renderables)
	{
		item->draw(0);
	}

	for (auto item : m_objects)
	{
		item.first->draw(0);
	}

	drawScoreLine(1, 0, 0, max(this->_highScore, player->particle->getPosition().x));
	drawScoreLine(0, 1, 0, max(this->_score, player->particle->getPosition().x));

	glEnable(GL_LIGHTING);

	//draw objects

	glEnable(GL_COLOR_MATERIAL);

}

void MyGlWindow::update()
{
	if (!run) return;

	float duration = 1. / 30;

	if (!this->slingshot->getForce()) {
		int s = std::ceil(player->particle->getPosition().x * 100.0f) / 100.0f;

		this->_score = max(this->_score, s);
	}
	this->_highScore = max(this->_score, this->_highScore);

	if (scoreCallback)
		scoreCallback(this->_score, this->_highScore);

	auto p = this->m_objects[0].first->particle->getPosition();
	auto p2 = this->floor->particle->getPosition();
	auto v = this->m_objects[0].first->particle->getVelocity();

	floor->setPosition(cyclone::Vector3(p.x + LEFT_POSITION, p2.y, p2.z));
	floor->setLeftX(p.x + LEFT_POSITION);
	water->setPosition(cyclone::Vector3(p.x, MIN_FLOOR_Y, 0));

	for (auto item : m_renderables)
	{
		item->update(duration);
	}

	for (auto item : m_objects)
	{
		item.first->update(duration);
	}

	// Contacts
	auto map = floor->getAnglePoints(player->particle->getPosition().x - player->getHeight(), player->particle->getPosition().x + player->getHeight());
	floor_contact->setDots(map);
	m_c_resolver->update(duration);
}

void MyGlWindow::focus_cam(cyclone::Particle* target) {
	auto p = target->getPosition();
	auto p2 = floor->particle->getPosition();
	auto v = target->getVelocity();
	auto zoom = 0.75 + std::log10(std::abs(v.x) + 0.5) / 2;

	if (game_step >= 2) {
		//	this->m_viewer->setZoom(zoom);
		//	this->m_viewer->setTranslate(glm::vec3{ p.x - 70 * (1 - zoom), p.y, p.z });
		m_viewer->centerAt(glm::vec3(p.x, p.y, p.z));
		m_viewer->lookFrom(glm::vec3(p.x, p.y, p.z) + glm::vec3(-5, 75, 75));
	} else {
		m_viewer->centerAt(glm::vec3(0, START_VALUE + 20, 0));
		m_viewer->lookFrom(glm::vec3(0, START_VALUE + 20, 0) + glm::vec3(0, 0, 75));
	}
}

void MyGlWindow::doPick()
{
	make_current();		// since we'll need to do some GL stuff

	int mx = Fl::event_x(); // where is the mouse?
	int my = Fl::event_y();

	// get the viewport - most reliable way to turn mouse coords into GL coords
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	// set up the pick matrix on the stack - remember, FlTk is
	// upside down!
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPickMatrix((double)mx, (double)(viewport[3] - my), 5, 5, viewport);

	// now set up the projection
	setProjection(false);

	// now draw the objects - but really only see what we hit
	GLuint buf[100];
	glSelectBuffer(100, buf);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);

	// draw the cubes, loading the names as we go
	for (size_t i = 0; i < m_objects.size(); ++i) {
		std::cout << "try pick: " << i << std::endl;
		glLoadName((GLuint)(i + 1));
		if (m_objects[i].second)
			m_objects[i].first->draw(0);
	}

	// go back to drawing mode, and see how picking did
	int hits = glRenderMode(GL_RENDER);
	if (hits) {
		// warning; this just grabs the first object hit - if there
		// are multiple objects, you really want to pick the closest
		// one - see the OpenGL manual 
		// remember: we load names that are one more than the index
		m_selected = buf[3] - 1;
		std::cout << "did hit" << std::endl;
	}
	else {// nothing hit, nothing selected
		m_selected = -1;
	}
	printf("Selected Cube %d\n", m_selected);
}



void MyGlWindow::setProjection(int clearProjection)
//==========================================================================
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, w(), h());
	if (clearProjection)
		glLoadIdentity();
	// compute the aspect ratio so we don't distort things
	double aspect = ((double)w()) / ((double)h());
	gluPerspective(fieldOfView, aspect, 1, 1000);

	// put the camera where we want it to be
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// use the transformation in the ArcBall

	gluLookAt(
		m_viewer->getViewPoint().x, m_viewer->getViewPoint().y, m_viewer->getViewPoint().z,
		m_viewer->getViewCenter().x, m_viewer->getViewCenter().y, m_viewer->getViewCenter().z,
		m_viewer->getUpVector().x, m_viewer->getUpVector().y, m_viewer->getUpVector().z
	);

	glDisable(GL_BLEND);
}

static int last_push;
int m_pressedMouseButton;
int m_lastMouseX;
int m_lastMouseY;

int MyGlWindow::handle(int e)
//==========================================================================
{
	switch (e) {
	case FL_SHOW:		// you must handle this, or not be seen!
		show();
		return 1;
	case FL_PUSH:
	{
		m_pressedMouseButton = Fl::event_button();
		m_lastMouseX = Fl::event_x();
		m_lastMouseY = Fl::event_y();

		if (m_pressedMouseButton == 1) {
			std::cout << "click" << std::endl;
			doPick();
			if (m_selected >= 0) {
				m_objects[m_selected].first->m_static = true;
				std::cout << "picked" << std::endl;
				game_step = 1;
			}
		}
		damage(1);
		return 1;
	}
	case FL_RELEASE:
		if (m_selected >= 0) {
			m_objects[m_selected].first->m_static = false;
			m_objects[m_selected].second = false;
			game_step = 2;
		}
		m_pressedMouseButton = -1;
		damage(1);
		return 1;
	case FL_DRAG: // if the user drags the mouse
	{

		double fractionChangeX = static_cast<double>(Fl::event_x() - m_lastMouseX) / static_cast<double>(this->w());
		double fractionChangeY = static_cast<double>(m_lastMouseY - Fl::event_y()) / static_cast<double>(this->h());

		if (m_pressedMouseButton == 1) {
			if (m_selected >= 0)
			{
				m_objects[m_selected].first->m_static = true;
				double r1x, r1y, r1z, r2x, r2y, r2z;
				getMouseLine(r1x, r1y, r1z, r2x, r2y, r2z);

				double rx, ry, rz;
				mousePoleGo(r1x, r1y, r1z, r2x, r2y, r2z,
					static_cast<double>(m_objects[m_selected].first->particle->getPosition().x),
					static_cast<double>(m_objects[m_selected].first->particle->getPosition().y),
					static_cast<double>(m_objects[m_selected].first->particle->getPosition().z),
					rx, ry, rz,
					1);
				m_objects[m_selected].first->particle->setPosition(rx, ry, rz);
			}
			else
			{
//				m_viewer->rotate(fractionChangeX, fractionChangeY);
			}
		}
		else if (m_pressedMouseButton == 2) {
//			m_viewer->zoom(fractionChangeY);
		}
		else if (m_pressedMouseButton == 3) {
//			m_viewer->translate(-fractionChangeX, -fractionChangeY, (Fl::event_key(FL_Shift_L) == 0) || (Fl::event_key(FL_Shift_R) == 0));
		}
		else {
			std::cout << "Warning: dragging with unknown mouse button!  Nothing will be done" << std::endl;
		}
//		std::cout << m_viewer->getViewPoint().x << " " << m_viewer->getViewPoint().y << " " << m_viewer->getViewPoint().z << ":"
//			<< m_viewer->getViewCenter().x << " " << m_viewer->getViewCenter().y << " " << m_viewer->getViewCenter().z << std::endl;
		m_lastMouseX = Fl::event_x();
		m_lastMouseY = Fl::event_y();
		redraw();
	}

	return 1;

	case FL_KEYBOARD:
		return 0;

	default:
		return 0;
	}
}


//
// get the mouse in NDC
//==========================================================================
void MyGlWindow::getMouseNDC(float& x, float& y)
//==========================================================================
{
	// notice, we put everything into doubles so we can do the math
	float mx = (float)Fl::event_x();	// remeber where the mouse went down
	float my = (float)Fl::event_y();

	// we will assume that the viewport is the same as the window size
	float wd = (float)w();
	float hd = (float)h();

	// remember that FlTk has Y going the wrong way!
	my = hd - my;

	x = (mx / wd) * 2.0f - 1.f;
	y = (my / hd) * 2.0f - 1.f;
}

