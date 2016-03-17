#pragma once
#include <Siv3D.hpp>

class EffectBase
{
public:
	EffectBase();
	~EffectBase();

	virtual void draw() = 0;

};

