#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "MyFiles/Display/IMyRender.h"

class WindEffect : public IMyRender {
private:
	struct Particle {
		glm::vec2 pt1;
		glm::vec2 pt2;
		glm::vec2 speed;
		float alpha;
	};

	float _angle;
	glm::vec2 _topLeftBorder;
	glm::vec2 _bottomRightBorder;
	std::vector<Particle> _elems;

	void _generate();

public:
	WindEffect(float angle, glm::vec2 topLeftBorder, glm::vec2 bottomRightBorder);
	void update(cyclone::real duration = 0) override;
	void draw(bool shadow) override;
};

