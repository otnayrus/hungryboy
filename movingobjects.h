#pragma once
#include <wx\dcclient.h>

class MovingObjects {
public:
	virtual void Move(int xAmount, int yAmount, int maxX, int maxY) = 0;
	virtual void Draw(wxPaintDC &dc) = 0;
};