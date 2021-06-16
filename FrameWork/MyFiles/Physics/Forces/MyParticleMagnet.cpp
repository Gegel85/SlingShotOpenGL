#include "MyParticleMagnet.h"

MyParticleMagnet::MyParticleMagnet(Vector3* anchor, real strenght, bool push, std::function<Vector3(Vector3 dir, real strength)> f_strength_curve) : AMyAnchoredForce(anchor)
{
	this->strenght = strenght;
	this->push = push;
	this->f_strength_curve = f_strength_curve;
}

void MyParticleMagnet::updateForce(Particle* particle, real duration)
{
	Vector3 dir = push ? (particle->getPosition() - *other) : (*other - particle->getPosition());
	particle->addForce(f_strength_curve(dir, strenght));
}
