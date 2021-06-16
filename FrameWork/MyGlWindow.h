
#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <Fl/Fl_Value_Slider.H>
#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <Fl/Fl_Double_Window.h>

#include "stdio.h"
#include "math.h"
#include "3DUtils.h"

#include "Vec3f.h"
#include "Viewer.h"
#include <vector>

#include "core.h"
#include "particle.h"
#include "MyFiles/Physics/Forces/MyBuoyancy.h"
#include "MyFiles/Physics/Objects/MyCube.h"

class MyGlWindow : public Fl_Gl_Window {
public:
	static const char* BALL;
	static const char* LASER;
	static const char* FIREBALL;
	static const char* FLOATER;
	static const char* ARTILLERY;
	static const char* PISTOL;

	MyGlWindow(int x, int y, int w, int h);

	std::vector<Vec3f*> history;

	Fl_Slider* time;
	int run;
	void update();
	void drawStuff();
	void doPick();
	void windActive(bool active);
	void cubeAction(int i);

private:
	void draw();					// standard FlTk

	void putText(char* string, int x, int y, float r, float g, float b);
	int handle(int);				// standard FlTk

	float fieldOfView;
	Viewer* m_viewer;
	char* m_mvt_type;
	MyWorldSpec* m_world;
	std::vector<IMyRender*> m_renderable;
	MyBuoyancy* fluid;
	std::vector<MyObject*> m_objects;
	int m_selected = -1;
	bool rotateCube = false;

	void setProjection(int clearProjection = 1);
	void getMouseNDC(float& x, float& y);
	void setupLight(float x, float y, float z);
};
