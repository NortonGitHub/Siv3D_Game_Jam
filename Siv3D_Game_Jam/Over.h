#pragma once
#include "SceneBase.h"
#include "Player.h"
class Over :
	public SceneBase
{
public:
	Over();
	Over(std::vector<Player*> _player);
	~Over();

	SceneBase* update() override;
	void draw() override;

private:
	int _finallyAllivingNum;

	Font topMessage;
	Font middleMessage;

	std::vector<Ellipse> _players;
};

