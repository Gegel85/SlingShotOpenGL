#pragma once
#include "MyColliders.h"

class MyCollisionResolver
{
public:
	MyCollisionResolver();

	std::vector<cyclone::AMyContact*> m_contacts;
	void update(cyclone::real duration);
protected:
	cyclone::ParticleContactResolver* m_resolver;
	cyclone::ParticleContact *m_contact = NULL;
};

