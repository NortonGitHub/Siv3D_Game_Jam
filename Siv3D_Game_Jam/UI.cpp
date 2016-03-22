#include "UI.h"
#include "Collision.h"


UI::UI(int _num)
	:_restHpFont(26),
	half_of_width(Window::Width() / 2),
	indicatingHPCoord{ Vec2(half_of_width - 240,410),Vec2(half_of_width - 80,410),Vec2{ half_of_width + 80,410 },Vec2{ half_of_width + 240,410 } }
{
	_hp = 0;
	_nowOpacity = 255;
	_beforeOpacity = _nowOpacity;

	indicatingHP.setSize(Vec2(40, 60));
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

void UI::update(std::vector<Player*> _player)
{
	bool _isCoveredWith = fluctuatingOpacity(_player);

	_nowOpacity = (_isCoveredWith) ? 55 : 255;
}

void UI::draw()
{
	/*
	indicatingHP.draw(Color(255, 255, 255, _opacityOfHpFont));
	_restHpFont(_hp).drawCenter(indicatingHP.center, Color(0, 0, 0, _opacityOfHpFont));
	*/
	indicatingHP.draw(Color(255, 255, 255, _nowOpacity));
	_restHpFont(_hp).drawCenter(indicatingHP.center, Color(0, 0, 0, _nowOpacity));

}

void UI::setPlayerHP(int hp)
{
	_hp = hp;
}

void UI::setOpacityOfHP(Ellipse _player)
{

}

bool UI::fluctuatingOpacity(std::vector<Player*> _player)
{
	for (auto p : _player) {
		if (Collision::isCollisionDetectionWithOpp(p->getEllipseBody(), indicatingHP)) {
			return true;
		}
	}
	return false;
}
