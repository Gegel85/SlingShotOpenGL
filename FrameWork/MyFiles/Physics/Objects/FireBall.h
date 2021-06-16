#pragma once
#include "MySphere.h"

class FireBall : virtual public MySphere
{
public:
	FireBall(const MyWorldSpec* env);

	virtual void reset() override;
	virtual void reset(cyclone::Vector3 pos) override;
	virtual void draw(bool shadow) override;
};

