#include "MySphere.h"
#include "../../../DrawUtils.H"

MySphere::MySphere(cyclone::real radius, cyclone::real mass, const MyWorldSpec* env) : MyObject(mass, env)
{
	this->radius = radius;
	m_drag = new cyclone::ParticleDrag(0.1, 0.01);
	particle->setDamping(0.99);
}

const cyclone::real MySphere::getDensity() const
{
	return particle->getMass() / getVolume();
}

const cyclone::real MySphere::getHeight() const
{
	return radius;
}

const cyclone::real MySphere::getVolume() const
{
	return 4.0 / 3.0 * pi * pow(radius, 3);
}

void MySphere::update(cyclone::real duration)
{
	forces->updateForces(duration);
	particle->integrate(duration);
}

void MySphere::draw(bool shadow)
{
	if (shadow)
		glColor3f(0.1, 0.1, 0.1);
	else
		glColor3f(radius, particle->getMass(), 0);
	glPushMatrix(); //save current coord system
	glTranslatef(particle->getPosition().x, particle->getPosition().y, particle->getPosition().z);
	glutSolidSphere(radius, 30, 30);
	glPopMatrix(); //restore the coord system
}
