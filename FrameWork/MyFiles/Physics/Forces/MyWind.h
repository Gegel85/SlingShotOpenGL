#pragma once
#include "../Objects/MyObject.h"

class MyWind : public cyclone::ParticleForceGenerator
{
public:
	float direction;
	float speed;
	MyWind(float direction, float speed);

	// H�rit� via ParticleForceGenerator
	virtual void updateForce(cyclone::Particle * particle, cyclone::real duration) override;
};

