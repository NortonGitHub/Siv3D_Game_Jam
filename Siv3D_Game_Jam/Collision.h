#pragma once
#include "CharaBase.h"
#include "Player.h"
#include"Enclosure.h"
#include <Siv3D.hpp>

class Collision
{
public:
	Collision();
	~Collision();

	static bool isCollisionDetection(Ellipse a, Rect b);
	static bool isCollisionDetectionWithOpp(Ellipse a, Ellipse b);

	static void CollisionDetection(std::vector<Player*>& _player, std::map<std::string, Enclosure*>& _enclosures,int _nowGameMode);


	static Point findAdjustmentCoord(std::string key, Rect a, int wr,int hr);
	static Point findAdjustmentCoordOpp(std::string key, Ellipse a, int wr, int hr);
	static void redistributedAcceleration(Player* & _p1, Player* & _p2);

private:
	bool discernedWinningAcceleration(Player* _p1, Player* _p2, bool& isAcceXValid);

	Player* tmp;

	double _acceXtmp;
	double _acceYtmp;
	bool _isTmpFull;

};

