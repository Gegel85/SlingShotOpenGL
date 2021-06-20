#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "Floor.h"
#include "MyFiles/Display/IMyRender.h"

class WindEffect : public IMyRender {
private:
	struct Particle {
		glm::vec2 pt1;
		glm::vec2 pt2;
		glm::vec2 speed;
		float alpha;
	};

	const Floor &_floor;
	float _angle;
	float _speed;
	glm::vec2 _topLeftBorder;
	glm::vec2 _bottomRightBorder;
	std::vector<Particle> _elems;

	void _generate();

public:
	WindEffect(const Floor &floor, float angle, glm::vec2 topLeftBorder, glm::vec2 bottomRightBorder, float wind_speed);
	void setAngle(float angle);
	void setSpeed(float speed);
	void update(cyclone::real duration = 0) override;
	void draw(bool shadow) override;
};

