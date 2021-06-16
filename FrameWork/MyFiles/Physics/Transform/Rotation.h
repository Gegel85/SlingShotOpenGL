#pragma once
#include <core.h>

class Rotation
{
	enum Enum_Euler_Order {
		XYZ,
		YZX,
		ZXY
	};

	cyclone::Vector3 euler;
	cyclone::Quaternion quaternion;

	Rotation();
	~Rotation();

	cyclone::Matrix4 getRotation() {
		cyclone::Matrix4 mat;
		mat.setOrientationAndPos(quaternion, cyclone::Vector3());
		return mat;
	}
};

