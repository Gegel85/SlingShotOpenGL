#pragma once
#include "MyObject.h"

class MyCube : public MyObject
{
protected:
	float size[3] = { 1, 1, 1 };
	void getGLTransform(float mat[16]);

public:
	float& width() { return size[0]; };
	float& height() { return size[1]; };
	float& lenght() { return size[2]; };

	MyCube(const float& w, const float& h, const float& l, const cyclone::real mass, const MyWorldSpec* env);

	// Hérité via MyObject
	using MyObject::update;
	virtual void draw(bool shadow) override;
};

