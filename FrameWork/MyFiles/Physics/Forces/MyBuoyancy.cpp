#include "MyBuoyancy.h"
#include <iostream>

using namespace cyclone;
MyBuoyancy::MyBuoyancy(const MyObject* obj, real _liquidLevelHeight, real _liquidDensity, MyWorldSpec* env) : ParticleForceGenerator(), m_env(env)
{
	if (obj)
	{
		objMaxDepth = obj->getHeight();
		volume = obj->getVolume();
	}
	height = _liquidLevelHeight;
	liquidDensity = _liquidDensity;
}

void MyBuoyancy::setTarget(const MyObject* obj)
{
	if (obj)
	{
		obj->forces->remove(obj->particle, this);
		objMaxDepth = obj->getHeight();
		volume = obj->getVolume();
		obj->forces->add(obj->particle, this);
	}
}

void MyBuoyancy::updateForce(Particle* p, real duration)
{
	cyclone::Vector3 force;
	cyclone::Vector3 pos = p->getPosition();
	double h = pos.y; //Particle�s y position

	if (h - objMaxDepth > height) {
	}
	else if (h + objMaxDepth < height) {
		force = cyclone::Vector3(0, volume * liquidDensity, 0);
	}
	else {
		double d = (height - (h - objMaxDepth)) / (2 * objMaxDepth);
		force = cyclone::Vector3(0, d * volume * liquidDensity, 0);
	}

	p->addForce(force);
}


void MyBuoyancy::update(cyclone::real duration)
{
}

void MyBuoyancy::draw(bool shadow)
{
	if (shadow)
		return;
	double h = 10.0;
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glPushMatrix();
	glColor4f(0, 0, 1, 0.2f);
	glTranslatef(0, height - h / 2, 0);
	drawCube(100, h, 100); //illustrate water
	glPopMatrix();
}

