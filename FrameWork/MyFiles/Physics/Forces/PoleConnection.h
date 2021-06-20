#pragma once
#include "AMyConnection.h"
#include "../Objects/MyObject.h"
#include "AMyAnchoredForce.h"
#include "FL/gl_draw.H"

class PoleConnection : public AMyConnection
{
public:
	PoleConnection(MyObject* obj1);
	~PoleConnection() {};

	void setForce(cyclone::AMyAnchoredForce* force);
	// Hérité via AMyConnection
	virtual void update(cyclone::real duration = 0) override;
	virtual void draw(bool shadow) override;
	const cyclone::AMyAnchoredForce* getForce();

protected:
	cyclone::AMyAnchoredForce* m_force;
};

