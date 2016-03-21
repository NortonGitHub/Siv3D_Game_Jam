#pragma once
#include "SceneBase.h"

#include "Player.h"
#include "Enclosure.h"
#include "Object.h"
#include "UI.h"

class Game :
	public SceneBase
{
public:
	Game();
	Game(int player_val,std::array<int,4> participant);
	~Game();

	SceneBase* update() override;
	void draw() override;

private:
	
	std::vector<Player*> player;
	
	std::map<std::string, Enclosure*> enclosures;
	std::vector<Object*> objects;

	std::vector<UI> _hpUI;
	
	//std::array<EffectManager*, 20> effects;
};

