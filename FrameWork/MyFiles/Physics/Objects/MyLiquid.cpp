#include "MyLiquid.h"

MyLiquid::MyLiquid(cyclone::real water_lvl, cyclone::real density, MyWorldSpec * env) : MyObject(1 , env)
{
	m_static = true;
	height = water_lvl;
	m_force = new MyBuoyancy(0, water_lvl, density, env);
}

void MyLiquid::update(cyclone::real duration)
{
	MyObject::update(duration);
	m_force->height = particle->getPosition().y + height;
}

void MyLiquid::draw(bool shadow)
{
	if (shadow)
		return;
	double depth = 10.0;
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glPushMatrix();
	glColor4f(0, 0, 1, 0.2f);
	auto pos = particle->getPosition();
	glTranslatef(pos.x, pos.y + (height - depth) / 2.0f , pos.z);
	drawCube(length, depth + height, width); //illustrate water
	glPopMatrix();
}
