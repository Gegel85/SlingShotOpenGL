#pragma once
#include "MyObject.h"
#include <particle.h>
#include <pfgen.h>
#include <FL\glut.H>

class MySphere : public MyObject
{
public:
	cyclone::real radius;

	MySphere(cyclone::real radius, cyclone::real mass, const MyWorldSpec* env);

	// Hérité via MyObject
	virtual const cyclone::real getDensity() const override;
	virtual const cyclone::real getHeight() const override;
	virtual const cyclone::real getVolume() const override;
	virtual void draw(bool shadow) override;

protected:
	cyclone::ParticleDrag* m_drag;
};

