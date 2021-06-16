#include "MyWorldSpec.h"

MyWorldSpec::MyWorldSpec(cyclone::Vector3 _gravity)
{
	g = _gravity;
	gravity = new cyclone::ParticleGravity(_gravity);
}

MyWorldSpec::~MyWorldSpec()
{
}
