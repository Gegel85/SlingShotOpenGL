#pragma once
#include "MySphere.h"

class Artillery : public MySphere
{
public:
	Artillery(const MyWorldSpec *env);

	virtual void reset() override;
	virtual void reset(cyclone::Vector3 pos) override;
	virtual void draw(bool shadow) override;
};

