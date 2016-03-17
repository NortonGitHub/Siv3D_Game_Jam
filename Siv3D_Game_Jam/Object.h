#pragma once
#include "CharaBase.h"
class Object :
	public CharaBase
{
public:
	Object(int x,int y,int r,std::string type);
	~Object();

	void update();
	void draw();

private:
	Rect rect;
	Triangle tri;
	Polygon Star;

	std::string elementType;

};

