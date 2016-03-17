#include "Object.h"




Object::Object(int x, int y, int r, std::string type)
{
	_x = x;
	_y = y;
	_wr = r;
	_hr = r;
	elementType = type;
}

Object::~Object()
{
}

void Object::update() {

}

void Object::draw() {
	if (elementType == "Rect") {
	}
	else if (elementType == "Triangle") {

	}
	else if (elementType == "Star") {

	}
}