#pragma once
#include "SceneBase.h"
class Over :
	public SceneBase
{
public:
	Over();
	~Over();

	SceneBase* update() override;
	void draw() override;
};

