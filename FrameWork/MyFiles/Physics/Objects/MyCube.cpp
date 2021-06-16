#include "MyCube.h"
#include <iostream>

MyCube::MyCube(const float& w, const float& h, const float& l, const cyclone::real mass, const MyWorldSpec* env) : MyObject(mass, env)
{
	size[0] = w;
	size[1] = h;
	size[2] = l;
}

void MyCube::getGLTransform(float matrix[16])
{
	matrix[0] = (float)transform.data[0];
	matrix[1] = (float)transform.data[4];
	matrix[2] = (float)transform.data[8];
	matrix[3] = 0;

	matrix[4] = (float)transform.data[1];
	matrix[5] = (float)transform.data[5];
	matrix[6] = (float)transform.data[9];
	matrix[7] = 0;

	matrix[8] = (float)transform.data[2];
	matrix[9] = (float)transform.data[6];
	matrix[10] = (float)transform.data[10];
	matrix[11] = 0;

	matrix[12] = (float)transform.data[3];
	matrix[13] = (float)transform.data[7];
	matrix[14] = (float)transform.data[11];
	matrix[15] = 1;
}


void MyCube::draw(bool shadow)
{
	GLfloat mat[16];
	getGLTransform(mat);  //convert transformMatrix to opengl-friendly 1D array
	if (shadow)
		glColor3f(0.1, 0.1, 0.1);
	else
		glColor3f(0.5, 0.5, 0);

	glPushMatrix();
	glMultMatrixf(mat);
	glutSolidCube(1.0f);
	if (!shadow)
		drawAxes(3);
	glPopMatrix();

}
