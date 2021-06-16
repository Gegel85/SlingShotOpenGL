#include "Pistol.h"

Pistol::Pistol(const MyWorldSpec* env) : MySphere(1.0f, 2.0f, env)
{
	particle->setVelocity(0.0f, 0.0f, 35.0f); // 35m/s
	particle->setAcceleration(0.0f, -1.0f, 0.0f);
	particle->setDamping(0.99f);
}

void Pistol::reset()
{
	MySphere::reset();
	particle->setVelocity(0.0f, 0.0f, 35.0f); // 35m/s
	particle->setAcceleration(0.0f, -1.0f, 0.0f);
	particle->setDamping(0.99f);
}

void Pistol::reset(cyclone::Vector3 pos)
{
	MySphere::reset(pos);
	particle->setVelocity(0.0f, 0.0f, 35.0f); // 35m/s
	particle->setAcceleration(0.0f, -1.0f, 0.0f);
	particle->setDamping(0.99f);
}

void Pistol::draw(bool shadow)
{
	if (shadow)
		glColor3f(0.1, 0.1, 0.1);
	else
		glColor3f(0.5, 0.5, 0.5);
	glPushMatrix(); //save current coord system
	glTranslatef(particle->getPosition().x, particle->getPosition().y, particle->getPosition().z);
	glutSolidSphere(radius, 30, 30);
	glPopMatrix(); //restore the coord system
}
