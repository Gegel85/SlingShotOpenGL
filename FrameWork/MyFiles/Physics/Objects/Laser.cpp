#include "Laser.h"

Laser::Laser(const MyWorldSpec* env) : MySphere(0.2f, 0.1f, env)
{
	forces->remove(particle, m_env->gravity);
	particle->setVelocity(0, 0, 100);
	particle->setAcceleration(0, 0, 0);
	particle->setDamping(0.99f);
}

void Laser::reset()
{
	MySphere::reset();
	particle->setVelocity(0, 0, 100);
	particle->setAcceleration(0, 0, 0);
	particle->setDamping(0.99f);
}

void Laser::reset(cyclone::Vector3 pos)
{
	MySphere::reset(pos);
	particle->setVelocity(0, 0, 100);
	particle->setAcceleration(0, 0, 0);
	particle->setDamping(0.99f);
}

void Laser::draw(bool shadow)
{
	if (shadow)
		glColor3f(0.1, 0.1, 0.1);
	else
		glColor3f(0.9, 1.0, 0.9);
	glPushMatrix(); //save current coord system
	glTranslatef(particle->getPosition().x, particle->getPosition().y, particle->getPosition().z);
	glutSolidSphere(radius, 30, 30);
	glPopMatrix(); //restore the coord system
}
