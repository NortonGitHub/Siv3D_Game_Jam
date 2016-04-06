#pragma once
#include "CharaBase.h"
#include "KeyBase.h"
#include"EffectManager.h"

class Player :
	public CharaBase
{
public:
	Player(int n, int all_player,int _gameMode);
	~Player();

	Player* update();
	void draw();

	void drawNormal();
	void drawBroken();

	void setAcceleration(double _x, double _y);

	void setEffectsInit(Point oponentAcce, Vec2 myCenter);

	int getHeightRadius() { return _hr; };
	int getWidthRadius() { return _wr; };

	double getAccelerationX() { return _accelerationX; }
	double getAccelerationY() { return _accelerationY; }

	void reflectingDamageToHP(Point opponent, int nowGameMode);
	void reflectingDamageToHPWithWall();

	void initPlayer(int n,int _gameMode);

	Ellipse getEllipseBody() { return Body; };

	std::string getMovingDirection() { return _direction; }

	bool isHPFallBelowZERO();
	int getHP() { return _hp; }
	int getPlayerNum() { return num; }

private:
	const int half_of_width;

	Ellipse Body;

	Circle yolk;
	std::array<Triangle, 4> eggShell;
	std::array<Player*, 4> processed;

	EffectManager effects;

	const Vec2 initialCoord[4];
	Gamepad usingpad;

	int frame;

	int num;
	int _hp;
	int _gottenStar;
	int _destroyedVal;
	int _stock;
	int allPlayerVal;

	Font font;	//テスト用

	bool _isBrokenCompleted;

	std::string _direction;//"right,left,up,down,stop"

	void initProcessedPlayer();
	void initBroken();

	void updateResistance();
	void rollDirection();
	void setMovingDirection();

	int getHPAccordingToTheModes(int _gameMode);
};

