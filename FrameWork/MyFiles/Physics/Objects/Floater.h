#pragma once
#include "MySphere.h"
#include "../Forces/MyParticleMagnet.h"

class Floater : virtual public MySphere
{
public:
	Floater(const MyWorldSpec* env);

	virtual void update(cyclone::real duration = 0) override;

protected:
	MyParticleMagnet* m_magnet;
};

