#include "Over.h"



Over::Over()
{
}

Over::Over(std::vector<Player*> _player)
	: topMessage(30)
	, middleMessage(26)
{
	_players.reserve(4);
	for (auto p : _player) {
		_players.push_back(p->getEllipseBody());
	}
}


Over::~Over()
{
}

SceneBase* Over::update()
{
	return this;
}

void Over::draw()
{
	topMessage(L"Standings").drawCenter(Window::Width() / 2, 60);
	
}
