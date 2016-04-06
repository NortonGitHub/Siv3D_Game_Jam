#include "GameResult.h"



GameResult::GameResult()
{
}


GameResult::GameResult(int livingNum, std::vector<Player*> _players)
	: font(30)
{
	_finallyLivingNum = livingNum;
	if (livingNum > 0) {
		_resultStr = "PLAYER _ WIN!";

		Player* winner = nullptr;
		for (auto p : _players) {
			if (p->getHP() > 0) {
				winner = p;
			}
		}

		assert(winner != nullptr);

		_resultStr.replace((int)_resultStr.find("_"), 1, std::to_string(winner->getPlayerNum()));

	}
	else {
		_resultStr = "DRAW...";
	}

	_toNextSceneTimer.restart();
}

GameResult::~GameResult()
{
}

bool GameResult::update()
{
	if (_toNextSceneTimer.ms() >= 5000) {
		_toNextSceneTimer.reset();
		return true;
	}
	return false;
}

void GameResult::draw()
{
	font(Widen(_resultStr)).drawCenter(Window::Center(), Palette::Yellow);
}
