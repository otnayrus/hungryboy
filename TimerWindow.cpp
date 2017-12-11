#include "TimerWindow.h"
#include "Food.h"
#include "Boy.h"
#include "Slider.h"
#include <wx/sizer.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#define TIMER_ID 2000


BEGIN_EVENT_TABLE(TimerWindow, wxWindow)
EVT_PAINT(TimerWindow::OnPaint)
EVT_TIMER(TIMER_ID, TimerWindow::OnTimer)
EVT_KEY_DOWN(TimerWindow::OnKeyDown)
EVT_KEY_UP(TimerWindow::OnKeyUp)
END_EVENT_TABLE()

TimerWindow::TimerWindow(wxFrame *frame) : wxWindow(frame, wxID_ANY) {
	srand(time(NULL));
	SetBackgroundColour(wxColour(*wxWHITE));
	timer = new wxTimer(this, TIMER_ID);
	mainc = new Boy(300, 300, 20, 10);
	seto = new Slider(0, 300, 20, 10, 10);

	wxImage::AddHandler(handler);
	
	//memulai timer dengan interval 25ms . bebas bisa diisi apa.
	timer->Start(50);
}

TimerWindow::~TimerWindow() {
	timer->Stop();
	delete timer;
	for (int i = 0; i < vc.size(); i++) {
		foodp = vc[i];
		delete foodp.first;
		delete foodp.second;
	}
	delete mainc;
	delete seto;
}

void TimerWindow::OnPaint(wxPaintEvent &event) {
	wxPaintDC pdc(this);
	mainc->Draw(pdc);
	seto->Draw(pdc);
	for (it = vc.begin(); it < vc.end(); it++) {
		food2p = *it;
		food2 = food2p.first;
		food2->Draw(pdc);
	}
}

void TimerWindow::OnTimer(wxTimerEvent &event) {
	static int counter = 0;
	wxMessageOutputDebug().Printf("wxTimer event %d.", counter++);
	if (counter % 25 == 0) {
		int temp = rand() % 3 - 2;
		if (temp > 0) {
			food = new Food(-25, rand() % 480, rand() % 70 + 20, rand() % 10 + 5);
			food->setxydir(1, 0);
			image = new wxStaticBitmap(this, wxID_ANY, wxBitmap("D:\\VStudio\\HungryHungryBoy\\HungryHungryBoy\\Debug\\f.png", wxBITMAP_TYPE_PNG), wxPoint(food->getx()-food->getRad(), food->gety() - food->getRad()), wxSize(2 * food->getRad(), 2 * food->getRad()));
		}
		else if (temp < 0) {
			food = new Food(GetClientSize().GetWidth() + 25, rand() % 480, rand() % 70 + 20, rand() % 10 + 5);
			food->setxydir(-1, 0);
			image = new wxStaticBitmap(this, wxID_ANY, wxBitmap("D:\\VStudio\\HungryHungryBoy\\HungryHungryBoy\\Debug\\f.png", wxBITMAP_TYPE_PNG), wxPoint(food->getx() - food->getRad(), food->gety() - food->getRad()), wxSize(2*food->getRad(), 2*food->getRad()));
		/*	bm = new wxBitmap("D:\\VStudio\\HungryHungryBoy\\HungryHungryBoy\\Debug\\f.png", wxBITMAP_TYPE_PNG);
			mage = bm->ConvertToImage();
			mage.Rescale(2 * food->getRad(), 2 * food->getRad());
			wxBitmap newbm(mage);
			image = new wxStaticBitmap(this, wxID_ANY, newb, wxPoint(food->getx() - food->getRad(), food->gety() - food->getRad()), wxSize(2*food->getRad(), 2*food->getRad())); */
		}
		else {
			temp = rand() % 3 - 2; 
			if (temp >= 0) {
				food = new Food(rand() % GetClientSize().GetWidth(), -25, rand() % 70 + 20, rand() % 10 + 5);
				food->setxydir(0 , 1);
				image = new wxStaticBitmap(this, wxID_ANY, wxBitmap("D:\\VStudio\\HungryHungryBoy\\HungryHungryBoy\\Debug\\f.png", wxBITMAP_TYPE_PNG), wxPoint(food->getx() - food->getRad(), food->gety() - food->getRad()), wxSize(2*food->getRad(), 2*food->getRad()));
			}
			else if (temp < 0) {
				food = new Food(rand() % GetClientSize().GetWidth(), GetClientSize().GetHeight() + 25, rand() % 70 + 20, rand() % 10 + 5);
				food->setxydir(0 , -1);
				image = new wxStaticBitmap(this, wxID_ANY, wxBitmap("D:\\VStudio\\HungryHungryBoy\\HungryHungryBoy\\Debug\\f.png", wxBITMAP_TYPE_PNG), wxPoint(food->getx() - food->getRad(), food->gety() - food->getRad()), wxSize(2*food->getRad(), 2*food->getRad()));
			}
		}
		vc.push_back(make_pair(food,image));
	}

	for (it = vc.begin(); it < vc.end();) {
		foodp = *it;
		food = foodp.first;
		image = foodp.second;
		dirX = food->getxdir();
		dirY = food->getydir();
		food->Move(food->getSpeed() * dirX, food->getSpeed() * dirY, GetClientSize().GetWidth(), GetClientSize().GetHeight());
		image->Move(wxPoint(food->getx() - food->getRad(), food->gety() - food->getRad()));
		it++;
	}
	for (it = vc.begin(); it < vc.end();) {
		foodp = *it;
		food = foodp.first;
		if (food->isOut(GetClientSize().GetWidth(), GetClientSize().GetHeight(), food->getxdir(), food->getydir())) {
			delete food;
			vc.erase(it);
			wxMessageOutputDebug().Printf("Object deleted");
			it = vc.begin();
		}
		else it++;
	}

	
	seto->Move(seto->getspeed(), seto->getspeed(), GetClientSize().GetWidth(), GetClientSize().GetHeight());
	if (seto->getx() > GetClientSize().GetWidth()) seto->respawn(mainc->getx(), mainc->gety());
	if (RectCircleCollide(mainc, seto)) {
		mainc->setHex(true);
		hexcounter = counter;
	}
	if (mainc->isHex()) {
		mainc->Hexed(20, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight());
		if (counter >= hexcounter + 10) {
			mainc->setHex(false);
			seto->respawn(mainc->getx(), mainc->gety());
		}
	}
	else mainc->Move(mainc->getSpeed(), mainc->getSpeed(), GetClientSize().GetWidth(), GetClientSize().GetHeight());
	Refresh();
}

void TimerWindow::OnKeyUp(wxKeyEvent &event)
{
	wxMessageOutputDebug().Printf("Key up event fired. Keycode=%d.",
		event.GetKeyCode());
	if (event.GetKeyCode() == 88) {
		boost = false;
		mainc->addSpeed(-25);
	}
}
 
void TimerWindow::OnKeyDown(wxKeyEvent &event)
{
	wxMessageOutputDebug().Printf("Key down event fired. Keycode=%d.", event.GetKeyCode());
	if (event.GetKeyCode() == WXK_UP)			mainc->setxydir(0,-1);
	else if (event.GetKeyCode() == WXK_RIGHT)	mainc->setxydir(1, 0);
	else if (event.GetKeyCode() == WXK_LEFT)	mainc->setxydir(-1, 0);
	else if (event.GetKeyCode() == WXK_DOWN)	mainc->setxydir(0, 1);

	if (event.GetKeyCode() == 88 && !boost) {
		boost = true;
		mainc->addSpeed(25);
	}
	event.Skip();
}

bool TimerWindow::RectCircleCollide(Boy * c, Slider *b) {
	int closestX = min(abs(b->getx() - c->getx()), abs(b->getx() - c->getx() + b->getw()));
	int closestY = min(abs(b->gety() - c->gety()), abs(b->gety() - c->gety() + b->geth()));

	return (closestX * closestX) + (closestY * closestY) < (c->getRad() * c->getRad());
}