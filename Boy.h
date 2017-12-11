#pragma once
#include <wx\dcclient.h>
#include "movingobjects.h"

class Boy : public MovingObjects
{
public:
	Boy(int x, int y, int rad, int speed);
	~Boy();
	virtual void Move(int xAmount, int yAmount, int maxX, int maxY);
	virtual void Draw(wxPaintDC &dc);
	void Hexed(int xAmount, int yAmount, int maxX, int maxY);
	bool isOut(int Xout, int Yout, int fromX, int fromY);
	int getx(void);
	int gety(void);
	int getRad(void);
	int getSpeed(void);
	int getxdir(void);
	int getydir(void);
	bool isHex(void);
	void setHex(bool h);
	void setxydir(int xdir, int ydir);
	void addSpeed(int speed);
private:
	//sizing
	int x, y, xDirection = 0, yDirection = 0, rad, speed, score;
	bool hex = 0;
};

