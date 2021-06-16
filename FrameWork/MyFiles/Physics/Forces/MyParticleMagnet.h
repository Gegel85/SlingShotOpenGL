#pragma once
#include "./AMyAnchoredForce.h"
#include <functional>

using namespace cyclone;

namespace cyclone {
	class MyParticleMagnet : public cyclone::AMyAnchoredForce
	{
	public:
		real strenght;
		bool push;
		std::function<Vector3(Vector3 dir, real strength)> f_strength_curve;

		MyParticleMagnet(Vector3* anchor, real strenght, bool push = false, std::function<Vector3(Vector3 dir, real strength)> f_strength_curve = [](Vector3 v, real s) { return v * s * (1 / v.magnitude()); });
		// Hérité via ParticleForceGenerator
		virtual void updateForce(Particle* particle, real duration) override;
	};
}