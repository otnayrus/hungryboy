#include "Boy.h"
#include "movingobjects.h"

Boy::Boy(int x, int y, int rad, int speed) : x(x), y(y), rad(rad), speed(speed) {

}

Boy::~Boy() {

}

void Boy::Draw(wxPaintDC &dc) {
	dc.SetBrush(wxBrush(wxColour(*wxGREEN)));
	dc.SetPen(wxPen(wxColor(*wxGREEN), 1, wxPENSTYLE_SOLID));
	dc.DrawCircle(wxPoint(this->x, this->y), wxCoord(this->rad));
}

void Boy::Move(int xAmount, int yAmount, int maxX, int maxY) {
	this->x += xAmount * xDirection;
	this->y += yAmount * yDirection;
}

void Boy::Hexed(int xAmount, int yAmount, int maxX, int maxY) {
	this->x += xAmount ;
	this->y += yAmount ;
}

int Boy::getx(void) {
	return this->x;
}

int Boy::gety(void) {
	return this->y;
}

int Boy::getRad(void) {
	return this->rad;
}

int Boy::getSpeed(void) {
	return this->speed;
}

int Boy::getxdir(void) {
	return this->xDirection;
}

int Boy::getydir(void) {
	return this->yDirection;
}

void Boy::setxydir(int xdir, int ydir) {
	this->xDirection = xdir;
	this->yDirection = ydir;
}

bool Boy::isHex(void) {
	return this->hex;
}

void Boy::setHex(bool h) {
	this->hex = h;
}

void Boy::addSpeed(int speed) {
	this->speed += speed;
}