#pragma once
#include <Siv3D.hpp>
class KeyBase
{
public:
	KeyBase();
	~KeyBase();

	static void inputKey(double &_acceX,double &_acceY,Gamepad pad);

};

