#include "ObjectConnection.h"

ObjectConnection::ObjectConnection(MyObject* obj1, MyObject* obj2)
{
	m_obj1 = obj1;
	m_obj2 = obj2;
}

void ObjectConnection::addForce(cyclone::ParticleForceGenerator* force)
{
	m_forces.push_back(force);
	m_obj1->forces->add(m_obj1->particle, force);
	m_obj2->forces->add(m_obj2->particle, force);
}

void ObjectConnection::removeForce(cyclone::ParticleForceGenerator* force)
{
	for (auto force : m_forces)
	{
		m_obj1->forces->remove(m_obj1->particle, force);
		m_obj2->forces->remove(m_obj2->particle, force);
	}
}

void ObjectConnection::removeForce(size_t at)
{
	if (at >= m_forces.size())
		return;
	m_obj1->forces->remove(m_obj1->particle, m_forces[at]);
	m_obj2->forces->remove(m_obj2->particle, m_forces[at]);
}

void ObjectConnection::update(cyclone::real duration)
{
	m_obj1->update(duration);
	m_obj2->update(duration);
}

void ObjectConnection::draw(bool shadow)
{
	glBegin(GL_LINE_STRIP);
	cyclone::Vector3 p = m_obj1->particle->getPosition();
	glVertex3f(p.x, p.y, p.z);
	p = m_obj2->particle->getPosition();
	glVertex3f(p.x, p.y, p.z);
	glEnd();
}
