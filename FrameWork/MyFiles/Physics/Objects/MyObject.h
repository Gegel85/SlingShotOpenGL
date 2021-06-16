#pragma once
#include "../../Display/IMyRender.h"
#include "../MyWorldSpec.h"
#include <iostream>

const float deg2Rad = 3.141592f / 180;
const float rad2Deg = 180 / 3.141592f;

class MyObject : public IMyRender {

public:
	cyclone::Particle* particle;
	cyclone::ParticleForceRegistry* forces;
	cyclone::Quaternion orientation;
	cyclone::Matrix4 transform;

	MyObject(cyclone::real mass, const MyWorldSpec* env);


	virtual void resetTranslation();
	virtual void resetTranslation(cyclone::Vector3 pos);

	void setPosition(cyclone::Vector3 p);
	void addRotation(const float amount, const cyclone::Vector3 axis);
	void setRotation(const float amount, const cyclone::Vector3 axis);
	cyclone::Matrix3 getAxisFromTransform();
	virtual const cyclone::real getDensity() const { return 0; };
	virtual const cyclone::real getHeight() const { return 0; };
	virtual const cyclone::real getVolume() const { return 0; };

	void drawAxes(float length);

	// Hérité via IMyRender
	virtual void update(cyclone::real duration = 0) override
	{
		forces->updateForces(duration);
		particle->integrate(duration);
		transform.data[3] = particle->getPosition().x;
		transform.data[7] = particle->getPosition().y;
		transform.data[11] = particle->getPosition().z;
	};
	virtual void draw(bool shadow) override = 0;

protected:
	const MyWorldSpec* m_env;
};