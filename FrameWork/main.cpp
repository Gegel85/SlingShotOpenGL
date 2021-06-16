// the main routine makes the window, and then runs an even loop
// until the window is closed
#include <windows.h>
#include <iostream>
#include <ctime>

#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <Fl/Fl_Value_Slider.H>
#include <Fl/Fl_Button.h>
#include <Fl/Fl_Light_Button.h>
#include <Fl/Fl_Choice.h>
#include <FL/Fl_Box.h>

#include "MyGlWindow.h"

#define min(a, b) ((a < b) ? a : b)


Fl_Group* widgets;


long lastRedraw;
int frameRate = 60;

void changeFrameCB(Fl_Widget* w, void* data)
{
	Fl_Choice* widget = (Fl_Choice*)w;
	int i = widget->value();
	const char* menu = widget->text(i);
	frameRate = atoi(menu);

	MyGlWindow* win = (MyGlWindow*)data;
	win->redraw();
}

void idleCB(void* w)
{
	MyGlWindow* win = (MyGlWindow*)w;
	if (clock() - lastRedraw > CLOCKS_PER_SEC / frameRate) {
		lastRedraw = clock();
		win->update();
	}
	win->redraw();
}

void bt_cb_run(Fl_Widget* o, void* data)
{
	Fl_Button* b = (Fl_Button*)o; //캐스팅이 반드시 필요
	MyGlWindow* win = (MyGlWindow*)data;
	if (b->value())
		win->run = 1;
	else
		win->run = 0;
	win->damage(1);
}


void bt_cb_wind(Fl_Widget* o, void* data)
{
	Fl_Button* b = (Fl_Button*)o; //캐스팅이 반드시 필요
	MyGlWindow* win = (MyGlWindow*)data;
	win->windActive(b->value());
	win->damage(1);
}

void bt_cb_cube_rotate(Fl_Widget* o, void* data)
{
	Fl_Button* b = (Fl_Button*)o; //캐스팅이 반드시 필요
	MyGlWindow* win = (MyGlWindow*)data;
	win->cubeAction(0);
	win->damage(1);
}

void bt_cb_cube_45y(Fl_Widget* o, void* data)
{
	Fl_Button* b = (Fl_Button*)o; //캐스팅이 반드시 필요
	MyGlWindow* win = (MyGlWindow*)data;
	win->cubeAction(1);
	win->damage(1);
}

void bt_cb_cube_90x(Fl_Widget* o, void* data)
{
	Fl_Button* b = (Fl_Button*)o; //캐스팅이 반드시 필요
	MyGlWindow* win = (MyGlWindow*)data;
	win->cubeAction(2);
	win->damage(1);
}

int main()
{
	Fl::scheme("plastic");// plastic
	int width = 900;
	int height = 800;
	int displayW = min(width - 120, 690);
	Fl_Double_Window* wind = new Fl_Double_Window(100, 100, width, height, "GL 3D FrameWork");

	wind->begin();		// put widgets inside of the window

	widgets = new Fl_Group(0, 0, 800, 800);
	widgets->begin();
	MyGlWindow* gl = new MyGlWindow(10, 10, displayW, height - 50);
	Fl::add_idle((void(*)(void*)) idleCB, gl);  //

	widgets->end();
	Fl_Group::current()->resizable(widgets);

	Fl_Choice* frame_rate;
	frame_rate = new Fl_Choice(100, height - 40, 50, 20, "FrameRate");
	frame_rate->add("15");
	frame_rate->add("30");
	frame_rate->add("60");
	frame_rate->value(2);
	frame_rate->callback((Fl_Callback*)changeFrameCB, gl);

	Fl_Light_Button* test = new Fl_Light_Button(200, height - 40, 100, 20, "Run");
	test->callback(bt_cb_run, gl);

//	Fl_Button* bt_wind = new Fl_Light_Button(350, height - 40, 100, 20, "Wind");
//	bt_wind->callback(bt_cb_wind, gl);

	Fl_Button* bt_continuous = new Fl_Light_Button(450, height - 40, 100, 20, "infinity");
	bt_continuous->callback(bt_cb_cube_rotate, gl);

	Fl_Button* bt_45y = new Fl_Button(550, height - 40, 100, 20, "45y");
	bt_45y->callback(bt_cb_cube_45y, gl);

	Fl_Button* bt_90x = new Fl_Button(650, height - 40, 100, 20, "45y90x");
	bt_90x->callback(bt_cb_cube_90x, gl);

	wind->end();

	wind->show();	// this actually opens the window

	Fl::run();
	delete wind;

	return 1;
}

