#pragma once
#include "CharaBase.h"
#include "KeyBase.h"
#include"EffectManager.h"

class Player :
	public CharaBase
{
public:
	Player(int padNum, int orderNum, int all_player);
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

	int getPlayerNumber() const { return playerNum; }
	int getOrderNumber()const { return orderNum; }

	void reflectingDamageToHP(Point opponent);
	void reflectingDamageToHPWithWall();

	void initPlayer(int n);

	Ellipse getEllipseBody() { return Body; };

	std::string getMovingDirection() { return _direction; }

	bool isHPFallBelowZERO();
	int getHP() { return _hp; }

private:
	const int half_of_width;

	Ellipse Body;

	Circle yolk;
	std::array<Triangle, 4> eggShell;

	EffectManager effects;

	const Vec2 initialCoord[4];
	Gamepad usingpad;

	int frame;

	int orderNum;	//参加順
	int playerNum;	//パッド番号
	int _hp;
	int allPlayerVal;

	Font font;	//テスト用

	bool _isBrokenCompleted;

	std::string _direction;//"right,left,up,down,stop"

	void initBroken();

	void updateResistance();
	void rollDirection();
	void setMovingDirection();

};

