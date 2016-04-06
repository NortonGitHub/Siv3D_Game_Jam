#pragma once
#include<Siv3D.hpp>
#include "GamePadManager.h"
class SceneBase
{
public:
	SceneBase();
	~SceneBase();

	virtual SceneBase* update() = 0;
	virtual void draw() = 0;

protected:
	enum GAME_MODE {
		DEATHMATCH,
		HUNTING,
		COLLECTOR
	};
};

