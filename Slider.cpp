#include "Slider.h"

Slider::Slider(int x, int y, int width, int height, int speed) : x(x), y(y), width(width), height(height), speed(speed)
{
}


Slider::~Slider()
{
}

void Slider::Draw(wxPaintDC &dc) {
	dc.SetBrush(wxBrush(wxColour(*wxBLACK)));
	dc.SetPen(wxPen(wxColor(*wxBLACK), 1, wxPENSTYLE_SOLID));
	dc.DrawRectangle(this->x, this->y, this->width, this->height);
}

void Slider::Move(int xAmount, int yAmount, int maxX, int maxY) {
	this->x += xAmount * xDirection;
	this->y += yAmount * yDirection;
}

bool Slider::isOut(int Xout, int Yout, int fromX, int fromY) {
	if (fromX == 1 && x - width >= Xout) {
		return true;
	}
	else if (fromX == -1 && x + width <= 0) {
		return true;
	}
	else if (fromY == 1 && y - height >= Yout) {
		return true;
	}
	else if (fromY == -1 && y + height <= 0) {
		return true;
	}
	return false;
}

int Slider::getx(void) {
	return this->x;
}
int Slider::gety(void) {
	return this->y;
}
int Slider::geth(void) {
	return this->height;
}
int Slider::getw(void) {
	return this->width;
}
int Slider::getspeed(void) {
	return this->speed;
}

int Slider::getxdir(void) {
	return this->xDirection;
}

int Slider::getydir(void) {
	return this->yDirection;
}

void Slider::respawn(int x, int y) {
	this->x = -15;
	this->y = y;
}