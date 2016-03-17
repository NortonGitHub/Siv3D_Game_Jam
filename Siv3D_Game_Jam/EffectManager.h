#pragma once
#include <Siv3D.hpp>
#include "Star.h"

class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	void init(Point oponentAcce, Vec2 myCenter,std::string direction);
	void update();
	void draw();

private:
	std::array<Star*, 5> _effectStar;
	
};

