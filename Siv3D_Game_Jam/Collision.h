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

	bool isCollisionDetection(Ellipse a, Rect b);
	bool isCollisionDetectionWithOpp(Ellipse a, Ellipse b);

	void CollisionDetection(std::vector<Player*>& _player, std::map<std::string, Enclosure*>& _enclosures);


	Point findAdjustmentCoord(std::string key, Rect a, int wr,int hr);
	Point findAdjustmentCoordOpp(std::string key, Ellipse a, int wr, int hr);

private:
	void redistributedAcceleration(Player* & _p1, Player* & _p2);
	bool discernedWinningAcceleration(Player* _p1, Player* _p2, bool& isAcceXValid);

	Player* tmp;

	double _acceXtmp;
	double _acceYtmp;
	bool _isTmpFull;

};

