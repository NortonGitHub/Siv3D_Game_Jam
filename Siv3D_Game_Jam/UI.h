#pragma once
#include <Siv3D.hpp>
#include "Player.h"

class UI
{
public:
	UI(int _num);
	~UI();

	void update(std::vector<Player*> _player);
	void draw();

	void init(int allNum);

	void setPlayerHP(int hp);
	void setOpacityOfHP(Ellipse _player);
private:
	const int half_of_width;
	const Vec2 indicatingHPCoord[4];

	bool fluctuatingOpacity(std::vector<Player*> _player);

	int _hp;

	Font _restHpFont;

	Ellipse indicatingHP;

	int _nowOpacity;
	int _beforeOpacity;

	Ellipse _coveringPlayer;
};

