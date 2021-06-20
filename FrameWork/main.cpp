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
#include <FL/Fl_Text_Display.H>
#include <Fl/Fl_Choice.h>
#include <FL/Fl_Box.h>

#include "MyGlWindow.h"

#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)

Fl_Group* widgets;
Fl_Text_Buffer* score_buff;
Fl_Text_Buffer* high_score_buff;

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

	score_buff->text("0");
	win->resetGame();
	win->damage(1);
}

void updateScore(int score, int maxScore) {
	score_buff->text(std::to_string(score).c_str());
	high_score_buff->text(std::to_string(maxScore).c_str());
}

int main()
{
	Fl::scheme("plastic");// plastic
	int width = 1080;
	int height = 720;
	Fl_Double_Window* wind = new Fl_Double_Window(100, 100, width, height, "SlingShot");
	score_buff = new Fl_Text_Buffer(11);
	high_score_buff = new Fl_Text_Buffer(11);
	wind->begin();		// put widgets inside of the window

	widgets = new Fl_Group(0, 0, 800, 800);
	widgets->begin();
	MyGlWindow* gl = new MyGlWindow(10, 10, width - 20, height - 50);
	gl->run = 1;
	gl->setScoreCallback(&updateScore);

	Fl::add_idle((void(*)(void*)) idleCB, gl);  //

	widgets->end();
	Fl_Group::current()->resizable(widgets);

	Fl_Button* reset = new Fl_Button(10, height - 30, 100, 20, "Reset");
	reset->callback(bt_cb_run, gl);

	Fl_Text_Display* score = new Fl_Text_Display(width / 2 - 100, height - 30, 90, 20);
	score->scrollbar_width(0);
	score->buffer(score_buff);
	score->align(FL_ALIGN_LEFT);
	score->label("Score");

	Fl_Text_Display* high_score = new Fl_Text_Display(width - 200, height - 30, 90, 20);
	high_score->scrollbar_width(0);
	high_score->buffer(high_score_buff);
	high_score->align(FL_ALIGN_LEFT);
	high_score->label("High Score");

	score_buff->text("0");
	high_score_buff->text("0");
	wind->end();

	wind->show();	// this actually opens the window

	Fl::run();
	delete wind;

	return 1;
}

