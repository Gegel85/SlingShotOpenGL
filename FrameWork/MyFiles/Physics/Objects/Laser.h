#pragma once
#include "MySphere.h"

class Laser : virtual public MySphere
{
public:
	Laser(const MyWorldSpec* env);

	virtual void reset() override;
	virtual void reset(cyclone::Vector3 pos) override;
	virtual void draw(bool shadow) override;
};

