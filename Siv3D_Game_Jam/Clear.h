#pragma once
#include "SceneBase.h"
class Clear :
	public SceneBase
{
public:
	Clear();
	~Clear();

	SceneBase* update() override;
	void draw() override;
};

