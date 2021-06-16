#include "MyAnchoredSpring.h"

cyclone::MyAnchoredSpring::MyAnchoredSpring(cyclone::Vector3* anchor, double springConstant, double restLenght) : AMyAnchoredForce(anchor)
{
	this->springConstant = springConstant;
	this->restLength = restLenght;
}

void cyclone::MyAnchoredSpring::updateForce(Particle* p, real duration)
{
	auto d = p->getPosition() - *other;
	Vector3 force = d.unit() * -springConstant * (d.magnitude() - restLength);
	
	p->addForce(force);

}
