#include "MyColliders.h"
#include <iostream>
#include<utility>

const float deg2Rad = 3.141592f / 180;
const float rad2Deg = 180 / 3.141592f;

using namespace cyclone;

unsigned int AMyContact::getMaxContactCount()
{
	return particles.size();
}


/// Plane
MyLinesContact::MyLinesContact(std::vector<cyclone::Vector3> dots)
{
	map = dots;
	while (map.size() < 2)
		map.push_back(cyclone::Vector3(0, 0, 0));
}


MyLinesContact::~MyLinesContact()
{
}


void MyLinesContact::init(cyclone::Particle* p, double size)
{
	if (p) {
		particles.emplace_back(p, false);
		this->size.push_back(size);
	}
}

void cyclone::MyLinesContact::setDots(std::vector<cyclone::Vector3> dots)
{
	map = dots;
	while (map.size() < 2)
		map.push_back(cyclone::Vector3(0, 0, 0));
}

unsigned MyLinesContact::addContact(cyclone::ParticleContact* contact, unsigned limit) const
{
	unsigned count = 0;
	bool is_colliding = false;

	for (int i = 0; i < particles.size(); i++)
	{
		auto pos = particles[i].first->getPosition();
		std::pair<cyclone::Vector3, float> contacts = std::make_pair(cyclone::Vector3(), 0);
		for (unsigned int j = 0; j < map.size() - 1; j++)
		{
			cyclone::Vector3 v1(map[j + 1].x - map[j].x, map[j + 1].y - map[j].y, 0);
			cyclone::Vector3 v2(pos.x - map[j].x, pos.y - map[j].y, 0);
			cyclone::Vector3 v3(pos.x - map[j + 1].x, pos.y - map[j + 1].y, 0);
			cyclone::Vector3 closest = map[j] + v1.unit() * v2.magnitude() * ((v1.x * v2.x + v1.y * v2.y) / (v1.magnitude() * v2.magnitude()));
			cyclone::Vector3 n = pos - closest;

			if (v2.magnitude() - size[i] < v1.magnitude() && v3.magnitude() - size[i] < v1.magnitude() && n.magnitude() < size[i])
			{
				is_colliding = true;
				if (particles[i].second == false) {
					if (onEnter != NULL) (*onEnter)(particles[i].first);
					particles[i].second = true;
				}
				else if (onStay != NULL) (*onStay)(particles[i].first);

				contacts.first += n.unit() * (size[i] - n.magnitude());
				contacts.second += size[i] - n.magnitude();
			}
		}
		if (is_colliding && !is_trigger) {
			contact->contactNormal = contacts.first.unit();
			contact->particle[0] = particles[i].first;
			contact->particle[1] = NULL;
			contact->penetration = contacts.second;
			contact->restitution = 1.0f;

			contact++;
			count++;
		}
		if (particles[i].second == true && !is_colliding) {
			if (onExit != NULL) (*onExit)(particles[i].first);
			particles[i].second = false;
		}
		is_colliding = false;
		if (count >= limit) return count;
	}
	return count;
}

cyclone::MyCircleContact::MyCircleContact(cyclone::Vector3 origin, cyclone::real radius)
{
	_origin = origin;
	_radius = radius;
}

cyclone::MyCircleContact::~MyCircleContact()
{
}

void cyclone::MyCircleContact::init(cyclone::Particle* p, double size)
{
	if (p)
	{
		particles.emplace_back(p, false);
		this->size.push_back(size);
	}
}

unsigned cyclone::MyCircleContact::addContact(cyclone::ParticleContact* contact, unsigned limit) const
{
	unsigned count = 0;
	bool is_colliding = false;

	for (int i = 0; i < particles.size(); i++)
	{
		cyclone::Vector3 d = particles[i].first->getPosition() - _origin;
		if (d.magnitude() < size[i] + _radius)
		{
			if (particles[i].second == false) {
				if (onEnter != NULL) (*onEnter)(particles[i].first);
				particles[i].second = true;
			}
			else if (onStay != NULL) (*onStay)(particles[i].first);
			if (!is_trigger) {
				contact->contactNormal = d.unit();
				contact->particle[0] = particles[i].first;
				contact->particle[1] = NULL;
				contact->penetration = size[i] + _radius - d.magnitude();
				contact->restitution = 1.0f;

				contact++;
				count++;
			}
		}
		if (particles[i].second == true && !is_colliding) {
			if (onExit != NULL) (*onExit)(particles[i].first);
			particles[i].second = false;
		}
		is_colliding = false;
		if (count >= limit) return count;
	}
	return count;
}

cyclone::MyRectContact::MyRectContact(cyclone::Vector3 p1, cyclone::Vector3 p2)
{
	this->p1 = p1;
	this->p2 = p2;
}

cyclone::MyRectContact::~MyRectContact()
{
}

void cyclone::MyRectContact::init(cyclone::Particle * p, double size)
{
	if (p)
	{
		particles.emplace_back(p, false);
		this->size.push_back(size);
	}
}

unsigned cyclone::MyRectContact::addContact(cyclone::ParticleContact * contact, unsigned limit) const
{
	unsigned count = 0;
	bool is_colliding = false;

	for (int i = 0; i < particles.size(); i++)
	{
		for (int j = 0; j < particles.size(); j++)
		{
			cyclone::Vector3 n = cyclone::Vector3();

			if (true)
			{
				if (particles[i].second == false) {
					if (onEnter != NULL) (*onEnter)(particles[i].first);
					particles[i].second = true;
				}
				else if (onStay != NULL) (*onStay)(particles[i].first);
				if (!is_trigger) {
					contact->contactNormal = n.unit();
					contact->particle[0] = particles[i].first;
					contact->particle[1] = NULL;
					contact->penetration = size[i] + size[j];
					contact->restitution = 1.0f;

					contact++;
					count++;
				}
			}

		}
		if (particles[i].second == true && !is_colliding) {
			if (onExit != NULL) (*onExit)(particles[i].first);
			particles[i].second = false;
		}
		is_colliding = false;
		if (count >= limit) return count;
	}
	return count;
}
