#pragma once
#include "SceneBase.h"

#include "Player.h"
#include "Enclosure.h"
#include "Object.h"
#include "PlayerStatus.h"
#include "GameResult.h"

class Game :
	public SceneBase
{
public:
	Game();
	Game(int player_val,std::array<int,4> participant,GAME_MODE _gameMode);
	~Game();

	SceneBase* update() override;
	void draw() override;

private:
	
	SceneBase* updateNormal();
	SceneBase* updateResult();

	void initGame();

	bool isSatisfiedClearCondition();

	std::vector<Player*> player;
	
	std::map<std::string, Enclosure*> enclosures;
	std::vector<Object*> objects;

	std::vector<PlayerStatus> _hpUI;

	std::array<int, 4> _participant;

	GameResult* _gameResult;

	enum GAME_MODE _nowGameMode;

	StopwatchMicrosec _limitedTime;

	int _nowAllivingNum;

	//std::array<EffectManager*, 20> effects;
};

