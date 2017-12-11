#pragma once
#include <wx\wx.h>
#include <vector>
#include "Boy.h"
#include "Slider.h"
using namespace std;

class Food;

class TimerWindow : public wxWindow {
public:
	TimerWindow(wxFrame *frame);
	~TimerWindow();
	void OnPaint(wxPaintEvent &event);
	void OnTimer(wxTimerEvent &event);
	void OnKeyDown(wxKeyEvent &event);
	void OnKeyUp(wxKeyEvent &event);
	bool RectCircleCollide(Boy * c, Slider * b);
	bool CircleCollide(Food * a, Boy *b);
	void Pause(void);
private:
	int dirX, dirY, hexcounter = 0 , mod = 12;
	bool boost = false, isPaused = false , isOver = false;
	wxTimer *timer;
	Boy * mainc;
	Slider * seto;
	Food * food, *food2;
	vector< Food * >vc;
	vector< Food * >::iterator it;
	vector< Food * >::iterator it2;

	vector<Slider *>vs;
	vector<Slider *>::iterator st;
	DECLARE_EVENT_TABLE()
};