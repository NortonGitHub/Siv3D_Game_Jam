#pragma once
#include "CharaBase.h"
class Enclosure :
	public CharaBase
{
public:
	Enclosure(double _x, double _y, int _w, int _h, Color _color);
	~Enclosure();

	void update();
	void draw();

	Rect wall;

};

