#pragma once
#include <core.h>
#include <pfgen.h>

class MyWorldSpec {
public:
	cyclone::ParticleGravity* wind;
	cyclone::ParticleGravity* gravity;
	cyclone::Vector3 g;

	MyWorldSpec(cyclone::Vector3 gravity);
	~MyWorldSpec();
};