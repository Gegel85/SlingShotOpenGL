#include "MyColliders.h"
#include <iostream>

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

	for (int i = 0; i < particles.size(); i++)
	{
		cyclone::Particle* p = particles[i].first;
		auto pos = p->getPosition();
		for (unsigned int j = 0; j < map.size() - 1; j++)
		{
			cyclone::Vector3 v1(map[j + 1].x - map[j].x, map[j + 1].y - map[j].y, 0);
			cyclone::Vector3 v2(pos.x - map[j].x, pos.y - map[j].y, 0);
			cyclone::Vector3 v3(pos.x - map[j + 1].x, pos.y - map[j + 1].y, 0);
			cyclone::Vector3 closest = map[j] + v1.unit() * v2.magnitude() * ((v1.x * v2.x + v1.y * v2.y) / (v1.magnitude() * v2.magnitude()));
			cyclone::Vector3 n = pos - closest;

			if (v2.magnitude() - size[i] < v1.magnitude() && v3.magnitude() - size[i] < v1.magnitude() && n.magnitude() < size[i])
			{
				contact->contactNormal = n.unit();
				contact->particle[0] = p;
				contact->particle[1] = NULL;
				contact->penetration = size[i] - n.magnitude();
				contact->restitution = 1.0f;

				contact++;
				count++;
			}
			if (count >= limit) return count;
		}
	}
	return count;
}

unsigned int cyclone::MyLinesContact::getMaxContactCount()
{
	return map.size() + particles.size();
}

cyclone::MyCircleContact::MyCircleContact()
{
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

	for (int i = 0; i < particles.size(); i++)
	{
		for (int j = 0; j < particles.size(); j++)
		{
			cyclone::Vector3 d = particles[i].first->getPosition() - particles[j].first->getPosition();
			if (d.magnitude() < size[i] + size[j])
			{
				contact->contactNormal = d.unit();
				contact->particle[0] = particles[i].first;
				contact->particle[1] = particles[j].first;
				contact->penetration = size[i] + size[j] - d.magnitude();
				contact->restitution = 1.0f;

				contact++;
				count++;
			}

		}
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
	return 0;
}
