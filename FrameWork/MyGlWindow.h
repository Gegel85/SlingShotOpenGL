
#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <Fl/Fl_Value_Slider.H>
#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <Fl/Fl_Double_Window.h>
#include <functional>

#include "stdio.h"
#include "math.h"
#include "3DUtils.h"

#include "Vec3f.h"
#include "Viewer.h"
#include <vector>

#include "core.h"
#include "particle.h"
#include "MyFiles/Physics/Forces/MyBuoyancy.h"
#include "MyFiles/Physics/Forces/PoleConnection.h"
#include "MyFiles/Physics/Forces/MyAnchoredSpring.h"
#include "MyFiles/Physics/Forces/MyWind.h"
#include "MyFiles/Physics/Objects/MySphere.h"
#include "MyFiles/Physics/Objects/MyLiquid.h"
#include "MyFiles/Physics/Collision/MyCollisionResolver.h"
#include "MyFiles/Physics/Collision/MyColliders.h"
#include "WindEffect.h"
#include "Floor.h"

class MyGlWindow : public Fl_Gl_Window {
public:
	static const char* BALL;
	static const char* LASER;
	static const char* FIREBALL;
	static const char* FLOATER;
	static const char* ARTILLERY;
	static const char* PISTOL;

	MyGlWindow(int x, int y, int w, int h);
	~MyGlWindow();

	std::vector<Vec3f*> history;

	Fl_Slider* time;
	int run;
	void resetGame();
	void update();
	void focus_cam(cyclone::Particle * target);
	void drawStuff();
	void doPick();
	void setScoreCallback(void(*callback)(int sessionScore, int maxScore)) {
		scoreCallback = callback;
	};

private:
	void draw();					// standard FlTk

	void putText(char* string, int x, int y, float r, float g, float b);
	int handle(int);				// standard FlTk

	int frames = 0;
	int _highScore = 0;
	int _score = 0;
	float fieldOfView;
	Viewer* m_viewer;
	char* m_mvt_type;
	MyWorldSpec* m_world;
	MyCollisionResolver* m_c_resolver;
	std::vector<IMyRender*> m_renderables;
	std::vector<std::pair<MyObject*, bool>> m_objects;
	PoleConnection *slingshot;
	MyLiquid* water;
	MyWind* wind_force;
	WindEffect* wind;
	Floor* floor;
	cyclone::MyLinesContact* floor_contact;
	MySphere* player;
	int game_step = 0;
	int m_selected = -1;
	std::function<void(cyclone::Particle*)> launch_ball;
	void (*scoreCallback)(int sessionScore, int maxScore);

	void setProjection(int clearProjection = 1);
	void getMouseNDC(float& x, float& y);
	void setupLight(float x, float y, float z);
	void setupForces();
	void setupObjects();
};
