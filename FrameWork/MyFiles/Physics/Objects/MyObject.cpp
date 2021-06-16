#include "MyObject.h"

MyObject::MyObject(cyclone::real mass, const MyWorldSpec* env) : m_env(env) {
	particle = new cyclone::Particle();
	forces = new cyclone::ParticleForceRegistry();
	particle->setMass(mass);
	particle->setDamping(0.99);
	forces->add(particle, env->gravity);
}

void MyObject::resetTranslation()
{
	particle->setPosition(0, 0, 0);
	particle->setVelocity(0, 0, 0);
	particle->setAcceleration(0, 0, 0);
}

void MyObject::resetTranslation(cyclone::Vector3 pos)
{
	particle->setPosition(pos);
	particle->setVelocity(0, 0, 0);
	particle->setAcceleration(0, 0, 0);
}

void MyObject::setPosition(cyclone::Vector3 p) {
	particle->setPosition(p);
	transform.data[3] = particle->getPosition().x;
	transform.data[7] = particle->getPosition().y;
	transform.data[11] = particle->getPosition().z;
};

void MyObject::addRotation(const float amount, const cyclone::Vector3 axis) {

	cyclone::Quaternion q;
	q.r = cos(deg2Rad * amount * 0.5f);
	cyclone::Vector3 v = axis.unit() * sin(deg2Rad * amount * 0.5f);
	q.i = v.x;
	q.j = v.y;
	q.k = v.z;
	q.normalise();

	orientation *= q;

	transform.setOrientationAndPos(orientation, particle->getPosition());
}

void MyObject::setRotation(const float amount, const cyclone::Vector3 axis) {
	orientation.r = cos(deg2Rad * amount * 0.5f);
	cyclone::Vector3 v = axis * sin(deg2Rad * amount * 0.5f);
	orientation.i = v.x;
	orientation.j = v.y;
	orientation.k = v.z;
	orientation.normalise();
	transform.setOrientationAndPos(orientation, particle->getPosition());
}

cyclone::Matrix3 MyObject::getAxisFromTransform() {
	cyclone::Matrix3 mat;
	mat.setComponents(transform.transformDirection(cyclone::Vector3(1, 0, 0)), transform.transformDirection(cyclone::Vector3(0, 1, 0)), transform.transformDirection(cyclone::Vector3(0, 0, 1)));
	return mat;
}

void MyObject::drawAxes(float l)
{
	cyclone::Vector3 o = particle->getPosition();
	//Draw axises
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, l, 0);

	glColor3f(0, 1, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(l, 0, 0);

	glColor3f(0, 0, 1);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, l);
	glEnd();
	glLineWidth(1.0f);
};
