#pragma once
#include <pfgen.h>


namespace cyclone {
	class AMyAnchoredForce : public ParticleForceGenerator
	{
	protected:
		cyclone::Vector3* other; //anchor

	public:
		AMyAnchoredForce(Vector3* anchor) { other = anchor; };

		const cyclone::Vector3* getAnchor() { return other; };
		void setAnchor(real x, real y, real z) { other->x = x; other->y = y; other->z = z; };

		// Hérité via ParticleForceGenerator
		virtual void updateForce(Particle* particle, real duration) override = 0;
	};
}