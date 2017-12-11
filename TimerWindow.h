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
private:
	int dirX, dirY, hexcounter = 0;
	bool boost = false;
	wxPNGHandler *handler = new wxPNGHandler;
	wxStaticBitmap *image,*image2;
	wxBitmap * bm;
	wxImage mage;
	wxTimer *timer;
	Boy * mainc;
	Slider * seto;
	pair< Food *, wxStaticBitmap * > foodp, food2p;
	Food * food, *food2;
	vector< pair< Food * , wxStaticBitmap * > >vc;
	vector< pair< Food *, wxStaticBitmap * > >::iterator it;
	vector< pair< Food *, wxStaticBitmap * > >::iterator it2;

	vector<Slider *>vs;
	vector<Slider *>::iterator st;
	DECLARE_EVENT_TABLE()
};