#pragma once
#include <pfgen.h>

namespace cyclone
{
	class MySpring : public cyclone::ParticleForceGenerator
	{
		cyclone::Particle* other; //Spring anchor
		cyclone::real springConstant; //Spring constant
		cyclone::real restLength; //lest length
	public:
		MySpring(cyclone::Particle* other, double springConstant, double restLenght);

		// Hérité via ParticleForceGenerator
		virtual void updateForce(Particle* particle, real duration) override;
	};
}
