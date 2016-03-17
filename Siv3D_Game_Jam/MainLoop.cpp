#include "MainLoop.h"
#include "Title.h"
#include "Game.h"

MainLoop::MainLoop()
{
#if 1
	_nowScene = new Title();
#endif
#if 0
	_nowScene = new Game();
#endif
}


MainLoop::~MainLoop()
{
}


void MainLoop::Main() {
	_nextScene = _nowScene->update();

	CheckSceneChanged();

	_nowScene->draw();
}

void MainLoop::CheckSceneChanged()
{
	if (_nextScene != _nowScene) {
		delete(_nowScene);
		_nowScene = _nextScene;
	}
}
