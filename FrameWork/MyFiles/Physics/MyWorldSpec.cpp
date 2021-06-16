#include "MyWorldSpec.h"

MyWorldSpec::MyWorldSpec(cyclone::Vector3 _gravity)
{
	g = _gravity;
	gravity = new cyclone::ParticleGravity(_gravity);
	wind = new cyclone::ParticleGravity(cyclone::Vector3());
}

MyWorldSpec::~MyWorldSpec()
{
}
