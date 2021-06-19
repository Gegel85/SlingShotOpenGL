#include "WindEffect.h"
#include "Floor.h"

#define NB_PARTICLES 30
#define MIN_SPEED 10
#define MAX_SPEED 30
#define MIN_LENGTH 30
#define MAX_LENGTH 100

WindEffect::WindEffect(float angle, glm::vec2 topLeftBorder, glm::vec2 bottomRightBorder) :
	_angle(angle),
	_topLeftBorder(topLeftBorder),
	_bottomRightBorder(bottomRightBorder)
{
	this->_elems.reserve(NB_PARTICLES);
	this->_generate();
}

void WindEffect::update(cyclone::real duration)
{
	for (int i = 0; i < this->_elems.size(); i++) {
		auto &elem = this->_elems[i];

		elem.pt1 += elem.speed;
		elem.pt2 += elem.speed;
		if (elem.pt1.x >= this->_bottomRightBorder.x || elem.pt1.y >= this->_bottomRightBorder.y) {
			this->_elems.erase(this->_elems.begin() + i);
			i--;
		}
	}
}

void WindEffect::draw(bool shadow)
{
	if (shadow)
		return;

	glBegin(GL_LINE);
	for (auto &elem : this->_elems) {
		glColor4f(0.90, 0.90, 0.90, elem.alpha);
		glVertex2f(elem.pt1.x, elem.pt1.y);
		glVertex2f(elem.pt2.x, elem.pt2.y);
	}
	glEnd();
}

void WindEffect::_generate()
{
	while (this->_elems.size() != NB_PARTICLES) {
		Particle particle;
		auto s = myRand(MIN_LENGTH, MAX_LENGTH);

		particle.alpha = myRand(0.25, 1);
		particle.pt1.x = myRand(this->_topLeftBorder.x, this->_bottomRightBorder.x);
		particle.pt1.y = myRand(this->_topLeftBorder.y, this->_bottomRightBorder.y);
		particle.pt2.x = particle.pt1.x + std::cos(this->_angle) * s;
		particle.pt2.y = particle.pt1.y + std::sin(this->_angle) * s;
		s = myRand(MIN_SPEED, MAX_SPEED);
		particle.speed.x = std::cos(this->_angle) * s;
		particle.speed.y = std::sin(this->_angle) * s;
		this->_elems.push_back(particle);
	}
}
