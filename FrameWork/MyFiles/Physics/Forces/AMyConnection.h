#pragma once
#include "../Objects/MyObject.h"

class AMyConnection : public IMyRender {
protected:
	MyObject* m_obj1;

public:
	// Hérité via IMyRender
	virtual void update(cyclone::real duration = 0) override = 0;
	virtual void draw(bool shadow) override = 0;
};