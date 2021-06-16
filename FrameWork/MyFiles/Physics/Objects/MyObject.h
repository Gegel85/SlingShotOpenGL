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

	void setPosition(cyclone::Vector3 p) {
		particle->setPosition(p);
		transform.data[3] = particle->getPosition().x;
		transform.data[7] = particle->getPosition().y;
		transform.data[11] = particle->getPosition().z;
	};

	void addRotation(const float amount, const cyclone::Vector3 axis) {

		cyclone::Quaternion q;
		q.r = cos(deg2Rad * amount * 0.5f);
		cyclone::Vector3 v = axis.unit() * sin(deg2Rad * amount * 0.5f);
		q.i = v.x;
		q.j = v.y;
		q.k = v.z;
		q.normalise();

		orientation *= q;

		transform.setOrientationAndPos(orientation, particle->getPosition());
	}

	void setRotation(const float amount, const cyclone::Vector3 axis) {
		orientation.r = cos(deg2Rad * amount * 0.5f);
		cyclone::Vector3 v = axis * sin(deg2Rad * amount * 0.5f);
		orientation.i = v.x;
		orientation.j = v.y;
		orientation.k = v.z;
		orientation.normalise();
		transform.setOrientationAndPos(orientation, particle->getPosition());
	}

	cyclone::Matrix3 getAxisFromTransform() {
		cyclone::Matrix3 mat;
		mat.setComponents(transform.transformDirection(cyclone::Vector3(1, 0, 0)), transform.transformDirection(cyclone::Vector3(0, 1, 0)), transform.transformDirection(cyclone::Vector3(0, 0, 1)));
		return mat;
	}

	virtual const cyclone::real getDensity() const { return 0; };
	virtual const cyclone::real getHeight() const { return 0; };
	virtual const cyclone::real getVolume() const { return 0; };

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
	void drawAxes(float length);

protected:
	const MyWorldSpec* m_env;
};