#include "./PoleConnection.h"

PoleConnection::PoleConnection(MyObject* obj1) : AMyConnection()
{
	m_obj1 = obj1;
}

void PoleConnection::setForce(cyclone::AMyAnchoredForce* force)
{
	m_obj1->forces->remove(m_obj1->particle, m_force);
	m_force = force;
	m_obj1->forces->add(m_obj1->particle, m_force);
}

void PoleConnection::update(cyclone::real duration)
{
	m_obj1->update(duration);
}

void PoleConnection::draw(bool shadow)
{
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	if (shadow)
		glColor3f(0.1, 0.1, 0.1);
	else
		glColor3f(0.95, 0.95, 0.95);
	glVertex3f(m_force->getAnchor()->x, m_force->getAnchor()->y, m_force->getAnchor()->z);
	glVertex3f(m_force->getAnchor()->x, 0, m_force->getAnchor()->z);
	glEnd();
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	if (shadow)
		glColor3f(0.1, 0.1, 0.1);
	else
		glColor3f(0.5, 0.5, 0.5);
	glColor3f(0.2, 0.2, 0.2);
	cyclone::Vector3 p = m_obj1->particle->getPosition();
	glVertex3f(p.x, p.y, p.z);
	glVertex3f(m_force->getAnchor()->x, m_force->getAnchor()->y, m_force->getAnchor()->z);
	glEnd();
}
