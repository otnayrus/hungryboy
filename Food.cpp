#include "Food.h"
#include "movingobjects.h"

Food::Food(int x, int y, int rad, int speed) : x(x), y(y), rad(rad), speed(speed) {
	int temp = rand() % 3 - 2;
	if (temp < 0) {
		this->score = -(rad);
		this->healthy = false;
	}
	else {
		this->score = rad;
		this->healthy = true;
	}
}

Food::~Food(){

}

void Food::Draw(wxPaintDC &dc) {
	if (this->healthy) dc.SetBrush(wxBrush(wxColour(*wxBLUE)));
	else dc.SetBrush(wxBrush(wxColour(*wxRED)));
	dc.SetPen(wxPen(wxColor(*wxWHITE), 1, wxPENSTYLE_SOLID));
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

bool Food::isHealthy(void) {
	return this->healthy;
}

void Food::setHealthy(bool h) {
	this->healthy = h;
}

int Food::getScore(void) {
	return this->score;
}