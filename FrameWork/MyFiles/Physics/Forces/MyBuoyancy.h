#pragma once
#include "../../../3DUtils.h"
#include "../Objects/MyObject.h"

class MyBuoyancy : public cyclone::ParticleForceGenerator
{
public:
	cyclone::real height;
	cyclone::real liquidDensity;
	cyclone::real objMaxDepth;
	cyclone::real volume;

	MyBuoyancy(const MyObject* obj, cyclone::real height, cyclone::real density, MyWorldSpec* env);

	void setTarget(const MyObject* obj);

	// H�rit� via ParticleForceGenerator	
	virtual void updateForce(cyclone::Particle* particle, cyclone::real duration) override;
private:
	MyWorldSpec *m_env;
};
