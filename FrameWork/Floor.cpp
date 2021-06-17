#include <limits>
#include <cassert>
#include <random>
#include <ctime>
#include "Floor.h"
#include "core.h"

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
	this->_points.reserve(sidesBeforeRepeat);
	this->_space = spaceBetweenSides;
	this->_min = minValue;
	this->_max = maxValue;
	do  {
		this->_points.push_back(startValue);
		startValue = randFct(startValue - maxDelta, startValue + maxDelta);
		startValue = max(min(startValue, maxValue), minValue);
	} while (--sidesBeforeRepeat);
	this->setLeftX(0);
}

std::vector<cyclone::Vector3> Floor::getAnglePoints(float x1, float x2)
{
	auto start = static_cast<int>(x1 / this->_space) % this->_points.size();
	auto end = x2 + this->_space - std::fmod(x2, this->_space);
	std::vector<cyclone::Vector3> list;
	float x = x1 - std::fmod(x1, this->_space);

	list.reserve((x - end) * this->_space);
	for (; x < x2; x += this->_space, start = (start + 1) % this->_points.size())
		list.emplace_back(x, this->_points[start], 0);
	assert((x - end) * this->_space == list.size());
	return list;
}

void Floor::setDepth(float depth)
{
	this->_depth = depth;
}

void Floor::setBottom(float y)
{
	this->_bottom = y;
}

void Floor::update(cyclone::real duration)
{

}

void Floor::draw(bool shadow)
{
	auto pt1 = this->_points[this->_left];

	if (shadow)
		glColor3f(0.1, 0.1, 0.1);
	glPushMatrix(); //save current coord system
	glTranslatef(particle->getPosition().x, particle->getPosition().y, particle->getPosition().z);
	
	glBegin(GL_QUADS);
	glColor3f(0.45, 0, 0);
	glVertex3f(0, this->_bottom, this->_depth);
	glVertex3f(this->_chunkSize * this->_space, this->_bottom, this->_depth);

	glColor3f(0.20, 0, 0);
	glVertex3f(this->_chunkSize * this->_space, this->_min, this->_depth);
	glVertex3f(0, this->_min, this->_depth);
	glEnd();

	glColor3f(0, (pt1 * this->_space) / this->_max, 0);
	for (unsigned i = 0, j = (this->_left + 1) % this->_points.size(); i < this->_chunkSize - 1; i++, j = (j + 1) % this->_points.size()) {
		auto pt2 = this->_points[j];

		glBegin(GL_QUADS);
		if (!shadow) {
			auto f = (pt1 - this->_min) / (this->_max - this->_min);

			glColor3f(0.2 * (1 - f), f, 0);
		}
		glVertex3f(i * this->_space - this->_leftPad, pt1, -this->_depth);
		glVertex3f(i * this->_space - this->_leftPad, pt1, this->_depth);

		if (!shadow) {
			auto f = (pt2 - this->_min) / (this->_max - this->_min);

			glColor3f(0.2 * (1 - f), f, 0);
		}
		glVertex3f((i + 1) * this->_space - this->_leftPad, pt2, this->_depth);
		glVertex3f((i + 1) * this->_space - this->_leftPad, pt2, -this->_depth);


		if (!shadow)
			glColor3f(0, (pt2 - this->_min) / (this->_max - this->_min), 0);
		glVertex3f((i + 1) * this->_space - this->_leftPad, pt2, this->_depth);
		if (!shadow)
			glColor3f(0, (pt1 - this->_min) / (this->_max - this->_min), 0);
		glVertex3f(i * this->_space - this->_leftPad, pt1, this->_depth);
		if (!shadow)
			glColor3f(0.20, 0, 0);
		glVertex3f(i * this->_space - this->_leftPad, this->_min, this->_depth);
		glVertex3f((i + 1) * this->_space - this->_leftPad, this->_min, this->_depth);

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
	if (x < 0)
		x -= this->_space;
	this->setLeft(static_cast<size_t>(
		this->_points.size() +
		static_cast<int>(x / this->_space) % static_cast<int>(this->_points.size())
	) % this->_points.size());
	this->_leftPad = fmod(this->_space + fmod(x, this->_space), this->_space);
}
