#pragma once
#include "MyObject.h"
#include "../Forces/MyBuoyancy.h"

class MyLiquid : public MyObject
{
public:
	cyclone::real height;
	MyBuoyancy* m_force;
	cyclone::real width = 100;
	cyclone::real length = 100;

	MyLiquid(cyclone::real water_lvl, cyclone::real density, MyWorldSpec* env);
	~MyLiquid() {};

	// Hérité via MyObject
	virtual void update(cyclone::real duration = 0) override;
	virtual void draw(bool shadow) override;
};

