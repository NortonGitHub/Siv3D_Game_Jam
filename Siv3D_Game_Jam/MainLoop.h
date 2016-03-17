#pragma once
#include "SceneBase.h"
class MainLoop
{
public:
	MainLoop();
	~MainLoop();

	void Main();

protected:
	SceneBase* _nowScene;
	SceneBase* _nextScene;

private:
	void CheckSceneChanged();
};

