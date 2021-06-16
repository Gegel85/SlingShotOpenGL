#include <limits>
#include <cassert>
#include <random>
#include <ctime>
#include "Floor.h"

float myRand(float min, float max)
{
	static std::mt19937 device( time(NULL) );
	static std::uniform_real_distribution<float> distribution(0, 1);

	distribution.param(std::uniform_real_distribution<float>::param_type(min, max));
	return distribution(device);
}

Floor::Floor(const MyWorldSpec* env, float depth, size_t sidesBeforeRepeat, float spaceBetweenSides, float minValue, float maxValue, float startValue, float maxDelta, float (*randFct)(float min, float max)) :
	MyObject(std::numeric_limits<cyclone::real>::infinity(), env),
	_depth(depth)
{
	this->regenerate(sidesBeforeRepeat, spaceBetweenSides, minValue, maxValue, startValue, maxDelta, randFct);
}

void Floor::regenerate(size_t sidesBeforeRepeat, float spaceBetweenSides, float minValue, float maxValue, float startValue, float maxDelta, float (*randFct)(float min, float max))
{
	assert(sidesBeforeRepeat > 0);
	this->_points.clear();
	this->_points.reserve(sidesBeforeRepeat + 1);
	this->_space = spaceBetweenSides;
	this->_min = minValue;
	this->_max = maxValue;
	do  {
		this->_points.push_back(startValue);
		printf("%f\n", startValue);
		startValue = randFct(startValue - maxDelta, startValue + maxDelta);
		startValue = max(min(startValue, maxValue), minValue);
	} while (sidesBeforeRepeat--);
}

std::pair<float, float> Floor::getVector(float x)
{
	auto v1 = static_cast<int>(x / this->_space) % this->_points.size();
	auto v2 = (static_cast<int>(x / this->_space) + 1) % this->_points.size();

	return { this->_points[v1], this->_points[v2] };
}

void Floor::setDepth(float depth)
{
	this->_depth = depth;
}

void Floor::update(cyclone::real duration)
{

}

void Floor::draw(bool shadow)
{
	auto pt1 = this->_points[this->_left];

	if (shadow)
		glColor3f(0.1, 0.1, 0.1);
	else
		glColor3f(0, (pt1 + this->_min) / this->_max, 0);
	glPushMatrix(); //save current coord system
	glTranslatef(particle->getPosition().x, particle->getPosition().y, particle->getPosition().z);

	for (unsigned i = 0, j = (this->_left + 1) % this->_points.size(); i < this->_chunkSize - 1; i++, j = (j + 1) % this->_points.size()) {
		auto pt2 = this->_points[j];

		glBegin(GL_QUADS);
		glVertex3f(i * this->_space, pt1, -this->_depth);
		glVertex3f(i * this->_space, pt1, this->_depth);

		if (!shadow)
			glColor3f(0, (pt2 + this->_min) / this->_max, 0);
		glVertex3f((i + 1) * this->_space, pt2, this->_depth);
		glVertex3f((i + 1) * this->_space, pt2, -this->_depth);
		glEnd();
		pt1 = pt2;
	}
	glPopMatrix(); //restore the coord system
}

void Floor::setChunkSize(size_t size)
{
	this->_chunkSize = size;
}

void Floor::setLeft(size_t left)
{
	this->_left = left;
}

void Floor::setLeftX(float x)
{
	this->setLeft(static_cast<int>(x / this->_space) % this->_points.size());
	this->_leftPad = fmod(x / this->_space, 1);
}
