#include "Star.h"



Star::Star()
{
}

Star::Star(Vec2 origin,std::string direction)
{
	time(&_passedTime);
	body = Geometry2D::CreateNStar(5, 20, 10, Random(TwoPi), origin);
	_movingDirection = direction;

	int _angle = getAngleOfMovement();

	_accerelationX = cos(_angle)*8.0;
	_accerelationY = sin(_angle)*8.0;

}


Star::~Star()
{
}

int Star::getAngleOfMovement()
{
	int _angle = 0;
	if (_movingDirection == "Left") {
		_angle = Random(135, 225);
	}
	else if (_movingDirection == "Right") {
		_angle = Random(-45, 45);
	}
	else if (_movingDirection == "Up") {
		_angle = Random(45, 135);
	}
	else if (_movingDirection == "Down") {
		_angle = Random(225, 315);
	}
	return _angle;
}

Star* Star::update()
{
	_accerelationX *= 0.85;
	_accerelationY *= 0.85;

	body.moveBy(_accerelationX, _accerelationY);

	if (_accerelationX <= 0.1 || _accerelationY <= 0.1) {
		return nullptr;
	}

	return this;
}

void Star::draw()
{
	body.draw();
}
