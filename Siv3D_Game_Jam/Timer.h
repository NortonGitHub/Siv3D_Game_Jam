#pragma once
#include "UIBase.h"
class Timer :
	public UIBase
{
public:
	Timer();
	~Timer();

	void draw() override;
};

