#pragma once
#include "EffectBase.h"
#include <time.h>

class Star :
	public EffectBase
{
public:
	Star();
	Star(Vec2 origin, std::string direction);
	~Star();

	Star* update();
	void draw() override;
	
private:
	Polygon body;

	std::string _movingDirection; 
	
	double _x;
	double _y;

	double _accerelationX; 
	double _accerelationY;

	int getAngleOfMovement();

	time_t _passedTime;
};

