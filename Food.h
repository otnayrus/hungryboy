#pragma once
#include <wx\dcclient.h>
#include "movingobjects.h"

class Food : public MovingObjects
{
public:
	Food(int x, int y, int rad, int speed);
	~Food();
	virtual void Move(int xAmount, int yAmount, int maxX, int maxY);
	virtual void Draw(wxPaintDC &dc);
	bool isOut(int Xout, int Yout, int fromX, int fromY);
	int getx(void);
	int gety(void);
	int getRad(void);
	int getSpeed(void);
	int getxdir(void);
	int getydir(void);
	void setxydir(int xdir, int ydir);
private:
	//sizing
	int x, y, xDirection, yDirection, rad, speed, score;
};

