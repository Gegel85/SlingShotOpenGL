#pragma once
#include <precision.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <FL/glut.H>

__interface IMyRender
{
public:
	virtual void update(cyclone::real duration = 0) = 0;
	virtual void draw(bool shadow) = 0;
};