#include "UI.h"
#include "Collision.h"


UI::UI(int _num)
	:_restHpFont(26),
	half_of_width(Window::Width() / 2),
	indicatingHPCoord{ Vec2(half_of_width - 210,410),Vec2(half_of_width - 90,410),Vec2{ half_of_width + 30,410 },Vec2{ half_of_width + 150,410 } }
{
	_hp = 0;
	_opacityOfHpFont = 255;

	indicatingHP.setSize(Vec2(60, 90));
	indicatingHP.setPos(indicatingHPCoord[_num]);
}

void UI::init(int allNum) {
#if 0
	for (int i = 0; i < allNum; i++) {
		indicatingHP.push_back(Ellipse(indicatingHPCoord[i], Vec2(60, 90)));
	}
#endif
}


UI::~UI()
{
}

void UI::update(Ellipse _player)
{
		fluctuatingOpacity(_player);
}

void UI::draw(int _hp)
{
	/*
	indicatingHP.draw(Color(255, 255, 255, _opacityOfHpFont));
	_restHpFont(_hp).drawCenter(indicatingHP.center, Color(0, 0, 0, _opacityOfHpFont));
	*/
	indicatingHP.draw(Color(255, 255, 255, _opacityOfHpFont));
	_restHpFont(_hp).drawCenter(indicatingHP.center, Color(0, 0, 0, _opacityOfHpFont));

}

void UI::setPlayerHP(int hp)
{
	_hp = hp;
}

void UI::fluctuatingOpacity(Ellipse _player)
{
	if (Collision::isCollisionDetectionWithOpp(_player, indicatingHP)) {
		if (_opacityOfHpFont > 55)
			_opacityOfHpFont -= 25;
	}
	else {
		if (_opacityOfHpFont < 255) {
	//		_opacityOfHpFont += 25;
		}
	}
}
