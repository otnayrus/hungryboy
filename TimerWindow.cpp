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
	
	//memulai timer dengan interval 25ms . bebas bisa diisi apa.
	timer->Start(50);
}

TimerWindow::~TimerWindow() {
	timer->Stop();
	delete timer;
	for (int i = 0; i < vc.size(); i++) {
		food = vc[i];
		delete food;
	}
	delete mainc;
	delete seto;
}

void TimerWindow::OnPaint(wxPaintEvent &event) {
	wxPaintDC pdc(this);
	mainc->Draw(pdc);
	seto->Draw(pdc);
	for (it = vc.begin(); it < vc.end(); it++) {
		food2 = *it;
		food2->Draw(pdc);
	}
}

void TimerWindow::OnTimer(wxTimerEvent &event) {
	static long long counter = 0;
	if (isOver) Pause();
	if (counter > 1000) mod = 6;
	wxMessageOutputDebug().Printf("wxTimer event %lld.", counter++);
	if (counter % mod == 0) {
		int temp = rand() % 3 - 2;
		if (temp > 0) {
			food = new Food(-25, rand() % 480, rand() % 50 + 10, rand() % 10 + 5);
			food->setxydir(1, 0);
			
		}
		else if (temp < 0) {
			food = new Food(GetClientSize().GetWidth() + 25, rand() % 480, rand() % 50 + 10, rand() % 10 + 5);
			food->setxydir(-1, 0);
		}
		else {
			temp = rand() % 3 - 2; 
			if (temp >= 0) {
				food = new Food(rand() % GetClientSize().GetWidth(), -25, rand() % 50 + 10, rand() % 10 + 5);
				food->setxydir(0 , 1);
			}
			else if (temp < 0) {
				food = new Food(rand() % GetClientSize().GetWidth(), GetClientSize().GetHeight() + 25, rand() % 50 + 10, rand() % 10 + 5);
				food->setxydir(0 , -1);
			}
		}
		vc.push_back(food);
	}

	for (it = vc.begin(); it < vc.end();) {
		food = *it;
		dirX = food->getxdir();
		dirY = food->getydir();
		food->Move(food->getSpeed() * dirX, food->getSpeed() * dirY, GetClientSize().GetWidth(), GetClientSize().GetHeight());
		it++;
	}
	for (it = vc.begin(); it < vc.end();) {
		food = *it;
		if (food->isOut(GetClientSize().GetWidth(), GetClientSize().GetHeight(), food->getxdir(), food->getydir())) {
			delete food;
			vc.erase(it);
			wxMessageOutputDebug().Printf("Object deleted");
			it = vc.begin();
		}
		else if (CircleCollide(food, mainc)) {
			mainc->addScore(food->getScore());
			delete food;
			vc.erase(it);
			wxMessageOutputDebug().Printf("Object deleted , eaten by Boy = %d",mainc->getScore());
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
	if (mainc->isOut(GetClientSize().GetWidth(), GetClientSize().GetHeight())) {
		if (mainc->lifemod(-1) == 0) isOver = true;
		mainc->respawn();
		if (mainc->isHex()) mainc->setHex(false);
	}
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
 

void TimerWindow::Pause(void) {
	if (isOver) {
		wxMessageOutputDebug().Printf("Game Over");
		timer->Stop();
		return;
	}
	isPaused = !isPaused;
	if (isPaused) {
		timer->Stop();
	}
	else timer->Start(50);
	Refresh();
}

void TimerWindow::OnKeyDown(wxKeyEvent &event)
{
	int keycode = event.GetKeyCode();
	wxMessageOutputDebug().Printf("Key down event fired. Keycode=%d.", keycode);
	if (keycode == 'p' || keycode == 'P') {
		Pause();
		return;
	}
	if (keycode == WXK_UP)			mainc->setxydir(0,-1);
	else if (keycode == WXK_RIGHT)	mainc->setxydir(1, 0);
	else if (keycode == WXK_LEFT)	mainc->setxydir(-1, 0);
	else if (keycode == WXK_DOWN)	mainc->setxydir(0, 1);

	if (keycode == 88 && !boost) {
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

bool TimerWindow::CircleCollide(Food * a, Boy * b) {
	if ((a->getx() - b->getx())*(a->getx() - b->getx()) + (a->gety() - b->gety())*(a->gety() - b->gety()) <= (double)((a->getRad() + b->getRad())*(a->getRad() + b->getRad()))) return true;
	return false;
}