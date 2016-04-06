#pragma once
#include "UIBase.h"
class GameBeReady :
	public UIBase
{
public:
	GameBeReady();
	~GameBeReady();

	bool update();
	void draw() override;

};

