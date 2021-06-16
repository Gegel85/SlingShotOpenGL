#pragma once
#include "AMyConnection.h"
#include <GL\glew.h>

class ObjectConnection : public AMyConnection
{
public:
	ObjectConnection(MyObject* obj1, MyObject* obj2);
	~ObjectConnection() {
		for (cyclone::ParticleForceGenerator* force : m_forces) {
			m_obj1->forces->remove(m_obj1->particle, force);
			m_obj2->forces->remove(m_obj2->particle, force);
		}
	};

	void addForce(cyclone::ParticleForceGenerator* force);
	void removeForce(cyclone::ParticleForceGenerator* force);
	void removeForce(size_t at);
	// Hérité via AMyConnnection
	virtual void update(cyclone::real duration = 0) override;
	virtual void draw(bool shadow) override;

protected:
	MyObject* m_obj2;

	std::vector<cyclone::ParticleForceGenerator* > m_forces;
};

