#include "MyFiles/Physics/Objects/MyObject.h"
#include <cstdlib>
#include <vector>
#include <map>

float myRand(float min, float max);

#pragma once
class Floor : public MyObject {
private:
	std::vector<float> _points;
	size_t _chunkSize = 50;
	size_t _left = 10;
	float _min;
	float _max;
	float _depth;
	float _space;

public:
	Floor(const MyWorldSpec* env, float depth = 10, size_t sidesBeforeRepeat = 100, float spaceBetweenSides = 4, float minValue = 10, float maxValue = 60, float startValue = 35, float maxDelta = 4, float (*randFct)(float min, float max) = myRand);
	void regenerate(size_t sidesBeforeRepeat = 100, float spaceBetweenSides = 4, float minValue = 0, float maxValue = 50, float startValue = 25, float maxDelta = 4, float (*randFct)(float min, float max) = myRand);
	void update(cyclone::real duration = 0) override;
	std::pair<float, float> getVector(float x);
	void setLeft(size_t left);
	void setLeftX(float x);
	void setDepth(float depth);
	void draw(bool shadow) override;
	void setChunkSize(size_t size);
};
