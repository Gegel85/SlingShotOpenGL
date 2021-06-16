#include "FireBall.h"


FireBall::FireBall(const MyWorldSpec* env) : MySphere(0.5f, 1.0f, env)
{
	forces->remove(particle, env->gravity);
	particle->setVelocity(0.0f, 0.0f, 10.0f); // 10m/s
	particle->setAcceleration(0.0f, 0.6f, 0.0f); // Floats up
	particle->setDamping(0.9f);
}

void FireBall::reset()
{
	MySphere::reset();
	particle->setVelocity(0.0f, 0.0f, 10.0f);
	particle->setAcceleration(0.0f, 0.6f, 0.0f);
	particle->setDamping(0.9f);
}

void FireBall::reset(cyclone::Vector3 pos)
{
	MySphere::reset(pos);
	particle->setVelocity(0.0f, 0.0f, 10.0f);
	particle->setAcceleration(0.0f, 0.6f, 0.0f);
	particle->setDamping(0.9f);
}

void FireBall::draw(bool shadow)
{
	if (shadow)
		glColor3f(0.1, 0.1, 0.1);
	else
		glColor3f(1.0, 0.1, 0.1);
	glPushMatrix(); //save current coord system
	glTranslatef(particle->getPosition().x, particle->getPosition().y, particle->getPosition().z);
	glutSolidSphere(radius, 30, 30);
	glPopMatrix(); //restore the coord system
}
