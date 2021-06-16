#include "MySpring.h"

cyclone::MySpring::MySpring(cyclone::Particle* anchor, double springConstant, double restLenght)
{
	other = anchor;
	this->springConstant = springConstant;
	this->restLength = restLenght;
}

void cyclone::MySpring::updateForce(Particle* p, real duration)
{
	auto d = p->getPosition() - other->getPosition();
	Vector3 force = d.unit() * -springConstant * (d.magnitude() - restLength);

	p->addForce(force);
}
