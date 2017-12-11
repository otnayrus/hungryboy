#include "Food.h"
#include "movingobjects.h"

Food::Food(int x, int y, int rad, int speed) : x(x), y(y), rad(rad), speed(speed) {

}

Food::~Food(){

}

void Food::Draw(wxPaintDC &dc) {
	dc.SetBrush(wxBrush(wxColour(*wxBLUE)));
	dc.SetPen(wxPen(wxColor(*wxBLACK), 1, wxPENSTYLE_SOLID));
	dc.DrawCircle(wxPoint(this->x, this->y), wxCoord(this->rad));
}

void Food::Move(int xAmount, int yAmount, int maxX, int maxY) {
	this->x += xAmount;
	this->y += yAmount;
}

bool Food::isOut(int Xout, int Yout, int fromX, int fromY) {
	if (fromX == 1 && x - rad >= Xout) {
		return true;
	}
	else if (fromX == -1 && x + rad <= 0) {
		return true;
	}
	else if (fromY == 1 && y - rad >= Yout) {
		return true;
	}
	else if (fromY == -1 && y + rad <= 0) {
		return true;
	}
	return false;
}

int Food::getx(void) {
	return this->x;
}

int Food::gety(void) {
	return this->y;
}

int Food::getRad(void) {
	return this->rad;
}

int Food::getSpeed(void) {
	return this->speed;
}

int Food::getxdir(void) {
	return this->xDirection;
}

int Food::getydir(void) {
	return this->yDirection;
}

void Food::setxydir(int xdir, int ydir) {
	this->xDirection = xdir;
	this->yDirection = ydir;
}