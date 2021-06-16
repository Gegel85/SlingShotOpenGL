#pragma once
#include "../../../3DUtils.h"
#include "../Objects/MyObject.h"

class MyBuoyancy : public cyclone::ParticleForceGenerator, public IMyRender
{
	const MyWorldSpec* m_env;

public:
	cyclone::real height;
	cyclone::real liquidDensity;
	cyclone::real objMaxDepth;
	cyclone::real volume;

	MyBuoyancy(const MyObject* obj, cyclone::real height, cyclone::real density, MyWorldSpec* env);

	void setTarget(const MyObject* obj);

	// Hérité via ParticleForceGenerator
	virtual void updateForce(cyclone::Particle* particle, cyclone::real duration) override;

	// Hérité via IMyRender
	virtual void update(cyclone::real duration = 0) override;
	virtual void draw(bool shadow) override;
};
