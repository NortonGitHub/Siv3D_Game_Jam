#include <Siv3D.hpp>
#include "KeyBase.h"
#include "GamePadManager.h"

KeyBase::KeyBase()
{}


KeyBase::~KeyBase()
{
}

void KeyBase::inputKey(double & _acceX, double & _acceY, Gamepad pad, std::string& _movingDirection)
{
	const double acceVal = 4.0;
	if (pad.povForward.clicked) {
		_movingDirection = "Up";
		_acceY -= acceVal;
		_acceX = 0.0;
	}
	else if (pad.povBackward.clicked) {
		_movingDirection = "Down";
		_acceY += acceVal;
		_acceX = 0.0;
	}
	else if (pad.povLeft.clicked) {
		_movingDirection = "Left";
		_acceX -= acceVal;
		_acceY = 0.0;
	}
	else if (pad.povRight.clicked) {
		_movingDirection = "Right";
		_acceX += acceVal;
		_acceY = 0.0;
	}
	else {
		_movingDirection = "Stop";
	}
}