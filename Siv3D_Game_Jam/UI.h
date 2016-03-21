#pragma once
#include <Siv3D.hpp>

class UI
{
public:
	UI(int _num);
	~UI();

	void update(Ellipse _player);
	void draw(int _hp);

	void init(int allNum);

	void setPlayerHP(int hp);
private:
	const int half_of_width;
	const Vec2 indicatingHPCoord[4];

	void fluctuatingOpacity(Ellipse _player);

	int _hp;

	Font _restHpFont;

	Ellipse indicatingHP;

	int _opacityOfHpFont;
};

