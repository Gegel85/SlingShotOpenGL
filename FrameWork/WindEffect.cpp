#include "WindEffect.h"
#include "Floor.h"

#define NB_PARTICLES 50
#define DELTA_SPEED 0.05
#define MIN_LENGTH 10
#define MAX_LENGTH 50

WindEffect::WindEffect(const Floor &floor, float angle, glm::vec2 topLeftBorder, glm::vec2 bottomRightBorder, float wind_speed) :
	_floor(floor),
	_angle(angle),
	_topLeftBorder(topLeftBorder),
	_bottomRightBorder(bottomRightBorder),
	_speed(wind_speed)

{
	this->_elems.reserve(NB_PARTICLES);
	this->_generate();
}

void WindEffect::setAngle(float angle)
{
	this->_angle = angle;
}

void WindEffect::setSpeed(float speed)
{
	this->_speed = speed;
}

void WindEffect::update(cyclone::real duration)
{
	for (int i = 0; i < this->_elems.size(); i++) {
		auto &elem = this->_elems[i];

		elem.pt1 += elem.speed;
		elem.pt2 += elem.speed;
		if (
			min(elem.pt1.x, elem.pt2.x) >= this->_bottomRightBorder.x ||
			min(elem.pt1.y, elem.pt2.y) >= this->_bottomRightBorder.y ||
			max(elem.pt1.x, elem.pt2.x) <= this->_topLeftBorder.x ||
			max(elem.pt1.y, elem.pt2.y) <= this->_topLeftBorder.y
		) {
			this->_elems.erase(this->_elems.begin() + i);
			i--;
		}
	}
	this->_generate();
}

void WindEffect::draw(bool shadow)
{
	if (shadow)
		return;

	glPushMatrix(); //save current coord system
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glTranslatef(this->_floor.particle->getPosition().x, this->_floor.particle->getPosition().y, this->_floor.particle->getPosition().z);
	glBegin(GL_LINES);
	for (auto &elem : this->_elems) {
		glColor4f(0.9, 0.9, 0.9, elem.alpha);
		glVertex3f(elem.pt1.x, elem.pt1.y, 0);
		glVertex3f(elem.pt2.x, elem.pt2.y, 0);
	}
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void WindEffect::_generate()
{
	while (this->_elems.size() != NB_PARTICLES) {
		Particle particle;
		auto s = myRand(MIN_LENGTH, MAX_LENGTH);

		particle.alpha = myRand(0.1, 1);
		particle.pt1.x = myRand(this->_topLeftBorder.x, this->_bottomRightBorder.x);
		particle.pt1.y = myRand(this->_topLeftBorder.y, this->_bottomRightBorder.y);
		particle.pt2.x = particle.pt1.x + std::cos(this->_angle) * s;
		particle.pt2.y = particle.pt1.y + std::sin(this->_angle) * s;
		s = myRand(max(0.1, _speed - _speed * DELTA_SPEED), _speed + _speed * DELTA_SPEED);
		particle.speed.x = std::cos(this->_angle) * s;
		particle.speed.y = std::sin(this->_angle) * s;
		this->_elems.push_back(particle);
	}
}
