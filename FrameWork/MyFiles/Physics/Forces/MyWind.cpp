#include "MyWind.h"

using namespace cyclone;

MyWind::MyWind(float dir, float spd) : 
	direction(dir), 
	speed(spd)
{
}

void MyWind::updateForce(Particle * p, real duration)
{
	p->addForce(cyclone::Vector3(cos(direction), sin(direction), 0) * speed);
}
