#pragma once
#include "./AMyAnchoredForce.h"

namespace cyclone
{
	class MyAnchoredSpring : public cyclone::AMyAnchoredForce
	{
		cyclone::real springConstant; //Spring constant
		cyclone::real restLength; //lest length
	public:
		MyAnchoredSpring(cyclone::Vector3* anchor, double springConstant, double restLenght);

		// Hérité via AMyAnchoredForce
		virtual void updateForce(Particle* particle, real duration) override;
	};
}
