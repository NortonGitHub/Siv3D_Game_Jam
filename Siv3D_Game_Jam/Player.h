#pragma once
#include "CharaBase.h"
#include "KeyBase.h"
#include"EffectManager.h"

class Player :
	public CharaBase
{
public:
	Player(int n,int all_player);
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

	void reflectingDamageToHP(Point opponent);
	void reflectingDamageToHPWithWall();

	void initPlayer(int n);

	Ellipse getEllipseBody() { return Body; };

	std::string getMovingDirection() { return _direction; }

	bool isHPFallBelowZERO();

private:


	Ellipse Body;

	Circle yolk;
	std::array<Triangle, 4> eggShell;

	EffectManager effects;

	const Vec2 initialCoord[4];
	Gamepad usingpad;

	void initBroken();

	void updateResistance();
	void rollDirection();
	void setMovingDirection();

	int frame;

	int num;
	int _hp;
	int allPlayerVal;

	Font font;	//テスト用

	bool _isBrokenCompleted;

	std::string _direction;//"right,left,up,down,stop"
};

