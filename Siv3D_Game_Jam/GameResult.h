#pragma once
#include <Siv3D.hpp>
#include <string>
#include "UIBase.h"
#include "Player.h"
class GameResult :
	public UIBase
{
public:
	GameResult();
	GameResult(int livingNum, std::vector<Player*> _players);
	~GameResult();
	
	bool update();
	void draw() override;

private:
	Vec2 playerNumCoord;
	Vec2 resultCoord;

	Font font;
	std::string _resultStr;

	StopwatchMicrosec _toNextSceneTimer;
	
	int _finallyLivingNum;
};

