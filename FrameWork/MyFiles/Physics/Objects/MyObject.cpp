#include "MyObject.h"

MyObject::MyObject(cyclone::real mass, const MyWorldSpec* env) : m_env(env) {
	particle = new cyclone::Particle();
	forces = new cyclone::ParticleForceRegistry();
	particle->setMass(mass);
}

void MyObject::drawAxes(float l)
{
	cyclone::Vector3 o = particle->getPosition();
	//Draw axises
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, l, 0);

	glColor3f(0, 1, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(l, 0, 0);

	glColor3f(0, 0, 1);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, l);
	glEnd();
	glLineWidth(1.0f);
};
