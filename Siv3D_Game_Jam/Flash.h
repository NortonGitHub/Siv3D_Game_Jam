#pragma once
#include "EffectBase.h"
class Flash :
	public EffectBase
{
public:
	Flash();
	~Flash();

	void update();
	void draw() override;
};

