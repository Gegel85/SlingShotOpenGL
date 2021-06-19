#include "MyCollisionResolver.h"
#include <iostream>

MyCollisionResolver::MyCollisionResolver()
{
	m_resolver = new cyclone::ParticleContactResolver(7);
}

void MyCollisionResolver::update(cyclone::real duration)
{
	unsigned limit = 0;
	unsigned max_contact = 0;
	for each (auto contact in m_contacts)
	{
		limit += contact->getMaxContactCount();
	}
	if (m_contact) free(m_contact);
	m_contact = new cyclone::ParticleContact[limit + 1];
	max_contact = limit;
	cyclone::ParticleContact* nextContact = m_contact;
	for (std::vector<cyclone::AMyContact*>::iterator g = m_contacts.begin();
		g != m_contacts.end();
		g++)
	{
		unsigned used = (*g)->addContact(nextContact, limit);
		limit -= used;
		nextContact += used;
		if (limit <= 0) break;
	}
	int num = max_contact - limit;

	if (num > 0) {
		m_resolver->setIterations(num * 2);
		m_resolver->resolveContacts(m_contact, num, duration);
	}
}
