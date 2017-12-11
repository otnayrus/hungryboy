#pragma once
#include "movingobjects.h"

class Slider : public MovingObjects
{
public:
	virtual void Move(int xAmount, int yAmount, int maxX, int maxY);
	virtual void Draw(wxPaintDC &dc);
	bool isOut(int Xout, int Yout, int fromX, int fromY);
	int getx(void);
	int gety(void);
	int geth(void);
	int getw(void);
	int getspeed(void);
	int getxdir(void);
	int getydir(void);
	void respawn(int x, int y);
	Slider(int x, int y, int width, int height, int speed);
	~Slider();
private:
	int x, y, width, height, speed, xDirection = 1, yDirection = 0;
};

