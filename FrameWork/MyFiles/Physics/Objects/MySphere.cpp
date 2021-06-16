#include "MySphere.h"
#include "../../DrawUtils.H"

MySphere::MySphere(cyclone::real radius, cyclone::real mass, const MyWorldSpec* env) : MyObject(mass, env)
{
	this->radius = radius;
	particle = new cyclone::Particle();
	m_drag = new cyclone::ParticleDrag(0.1, 0.01);
	forces = new cyclone::ParticleForceRegistry();
	particle->setMass(mass);
	particle->setDamping(0.99);
	forces->add(particle, m_env->gravity);
	forces->add(particle, m_env->wind);
	forces->add(particle, m_drag);
}

void MySphere::reset()
{
	particle->setVelocity(0, 0, 0);
	particle->setPosition(0, 0, 0);
	particle->setAcceleration(0, 0, 0);
}

void MySphere::reset(cyclone::Vector3 pos)
{
	particle->setVelocity(0, 0, 0);
	particle->setPosition(pos);
	particle->setAcceleration(0, 0, 0);
}

void MySphere::checkEdges()
{
	auto velocity = particle->getVelocity();
	if (particle->getPosition().y - radius < 0) {
		particle->setPosition(particle->getPosition().x, radius, particle->getPosition().z);
		particle->setVelocity(velocity.x, -velocity.y, velocity.z);
	}
	if (abs(particle->getPosition().x) + radius > cyclone::real(100)) {
		particle->setPosition((particle->getPosition().x >= 0 ? 1 : -1) * (100 - radius), particle->getPosition().y, particle->getPosition().z);
		particle->setVelocity(-velocity.x, velocity.y, velocity.z);
	}
}

const cyclone::real MySphere::getDensity() const
{
	return particle->getMass() / getVolume();
}

const cyclone::real MySphere::getHeight() const
{
	return radius;
}

const cyclone::real MySphere::getVolume() const
{
	return 4.0 / 3.0 * pi * pow(radius, 3);
}

void MySphere::update(cyclone::real duration)
{
	forces->updateForces(duration);
	particle->integrate(duration);

	//	checkEdges();
}

void MySphere::draw(bool shadow)
{
	if (shadow)
		glColor3f(0.1, 0.1, 0.1);
	else
		glColor3f(radius, particle->getMass(), 0);
	glPushMatrix(); //save current coord system
	glTranslatef(particle->getPosition().x, particle->getPosition().y, particle->getPosition().z);
	glutSolidSphere(radius, 30, 30);
	glPopMatrix(); //restore the coord system
}
