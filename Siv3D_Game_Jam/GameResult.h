#pragma once
#include <Siv3D.hpp>
#include "UIBase.h"
class GameResult :
	public UIBase
{
public:
	GameResult();
	GameResult(int livingNum);
	~GameResult();
	
	void update();
	void draw() override;

private:
	Vec2 playerNumCoord;
	Vec2 resultCoord;

	Font font;
	
	int _finallyLivingNum;
};

