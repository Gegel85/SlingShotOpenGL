#include "Artillery.h"

Artillery::Artillery(const MyWorldSpec* env) : MySphere(2, 200.0f, env)
{
	particle->setVelocity(0.0f, 30.0f, 40.0f); // 50m/s
	particle->setAcceleration(0.0f, -20.0f, 0.0f);
	particle->setDamping(0.99f);
}

void Artillery::reset()
{
	MySphere::reset();
	particle->setVelocity(0.0f, 30.0f, 40.0f); // 50m/s
	particle->setAcceleration(0.0f, -20.0f, 0.0f);
	particle->setDamping(0.99f);
}

void Artillery::reset(cyclone::Vector3 pos)
{
	MySphere::reset(pos);
	particle->setVelocity(0.0f, 30.0f, 40.0f); // 50m/s
	particle->setAcceleration(0.0f, -20.0f, 0.0f);
	particle->setDamping(0.99f);
}

void Artillery::draw(bool shadow)
{
	if (shadow)
		glColor3f(0.1, 0.1, 0.1);
	else
		glPushMatrix(); //save current coord system
	glTranslatef(particle->getPosition().x, particle->getPosition().y, particle->getPosition().z);
	glutSolidSphere(radius, 10, 10);
	glPopMatrix(); //restore the coord system
}
