#include "Floater.h"

Floater::Floater(const MyWorldSpec* env) : MySphere(1.0f, 1.0f, env)
{
	m_magnet = new MyParticleMagnet(new cyclone::Vector3(), 1.0f, false, [](cyclone::Vector3 v, cyclone::real s) {return v.unit() * s; });
	particle->setDamping(1);
	forces->remove(particle, m_env->gravity);
	forces->remove(particle, m_drag);
	forces->add(particle, m_magnet);
}

void Floater::update(cyclone::real duration)
{
	m_magnet->setAnchor(particle->getPosition().x, 10.0, particle->getPosition().z);
	forces->updateForces(duration);
	particle->integrate(duration);

	checkEdges();
}
