#include "Enclosure.h"
#include "Collision.h"

Enclosure::Enclosure(double _x, double _y, int _w, int _h, Color _color)
{
	color = _color;
	wall.set(_x, _y, _w, _h);
}

Enclosure::~Enclosure()
{
}

void Enclosure::update()
{
}

void Enclosure::draw()
{
	wall.draw(color);
}
