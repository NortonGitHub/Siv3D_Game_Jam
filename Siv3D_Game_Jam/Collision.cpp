#include "Collision.h"


Collision::Collision()
{
	_isTmpFull = false;
}


Collision::~Collision()
{
}

bool Collision::isCollisionDetection(Ellipse a, Rect b)
{
	if (a.intersects(b)) {
		return true;
		
	}
	return false;
}

bool Collision::isCollisionDetectionWithOpp(Ellipse a, Ellipse b)
{
#if 0
	if (a.intersects(b)) {
		return true;
	}

	int distanceX = a.center.x - b.center.x;
	int distanceY = a.center.y - b.center.y;
	int bothAxis = a.a + b.a;
	
	if (sqrt(distanceX*distanceX + distanceY*distanceY) >= bothAxis) {
		return true;
	}
#endif

	/*marupeke296.com/COL_2D_No7_EllipseVsEllipse.html ‚æ‚èˆø—p*/

	float Cos = cos(0.0);
	float Sin = sin(0.0);
	float nx = b.a*Cos;
	float ny = -b.a*Sin;
	float px = b.b*Sin;
	float py = b.b*Cos;
	float ox = Cos*(b.center.x - a.center.x) + Sin*(b.center.y - a.center.y);
	float oy = -Sin*(b.center.x - a.center.x) + Cos*(b.center.y - a.center.y);

	float rx_pow2 = 1 / (a.a*a.a);
	float ry_pow2 = 1 / (a.b*a.b);
	float A = rx_pow2*nx*nx + ry_pow2*ny*ny;
	float B = rx_pow2*px*px + ry_pow2*py*py;
	float D = 2 * rx_pow2*nx*px + 2 * ry_pow2*ny*py;
	float E = 2 * rx_pow2*nx*ox + 2 * ry_pow2*ny*oy;
	float F = 2 * rx_pow2*px*ox + 2 * ry_pow2*py*oy;
	float G = (ox / a.a)*(ox / a.a) + (oy / a.b)*(oy / a.b) - 1;

	float tmp1 = 1 / (D*D - 4 * A*B);
	float h = (F*D - 2 * E*B)*tmp1;
	float k = (E*D - 2 * A*F)*tmp1;
	float Th = (B - A) == 0 ? 0 : atan(D / (B - A))*0.5f;

	float CosTh = cos(Th);
	float SinTh = sin(Th);
	float A_tt = A*CosTh*CosTh + B*SinTh*SinTh - D*CosTh*SinTh;
	float B_tt = A*SinTh*SinTh + B*CosTh*CosTh + D*CosTh*SinTh;
	float KK = A*h*h + B*k*k + D*h*k - E*h - F*k + G;

	if (KK > 0) KK = 0;

	float Rx_tt = 1 + sqrt(-KK / A_tt);
	float Ry_tt = 1 + sqrt(-KK / B_tt);
	float x_tt = CosTh*h - SinTh*k;
	float y_tt = SinTh*h + CosTh*k;
	float JusgeValue = x_tt*x_tt / (Rx_tt*Rx_tt) + y_tt*y_tt / (Ry_tt*Ry_tt);

	if (JusgeValue <= 1) {
		return true;
	}

	return false;
}

void Collision::CollisionDetection(std::vector<Player*>& _player, std::map<std::string, Enclosure*>& _enclosures)
{
	for (auto it : _player) {
		if (it->isHPFallBelowZERO())
			continue;

		auto vir_pl = it->getEllipseBody();
		vir_pl.x += it->getAccelerationX();
		vir_pl.y += it->getAccelerationY();


		for (std::map<std::string, Enclosure*>::iterator en = _enclosures.begin(); en != _enclosures.end(); en++) {
			en->second->update();
			if (isCollisionDetection(vir_pl, en->second->wall)) {
				Point _acce = Point(it->getAccelerationX(), it->getAccelerationY());
				it->getEllipseBody().setPos(findAdjustmentCoord(en->first, en->second->wall, it->getWidthRadius() / 2, it->getHeightRadius() / 2));
				it->setEffectsInit(_acce, vir_pl.center);
				it->reflectingDamageToHPWithWall();
				it->setAcceleration(it->getAccelerationX()*-1, it->getAccelerationY()*-1);
			}
		}

		for (auto it2 : _player) {

			if (it2->isHPFallBelowZERO())
				continue;

#if 1
			auto vir_pl2 = it2->getEllipseBody();
			vir_pl2.x += it2->getAccelerationX();
			vir_pl2.y += it2->getAccelerationY();
#endif
			if (it != it2) {
				if (isCollisionDetectionWithOpp(vir_pl,vir_pl2)) {
					Point _acce1 = Point(it->getAccelerationX(), it->getAccelerationY());
					Point _acce2 = Point(it2->getAccelerationX(), it2->getAccelerationY());
					
					it->setEffectsInit(_acce2, vir_pl.center);
					it2->setEffectsInit(_acce1, vir_pl2.center);
					
					it->reflectingDamageToHP(_acce2);
					it2->reflectingDamageToHP(_acce1);
					redistributedAcceleration(it, it2);
					return;
				}
			}
		}
	}



#if 0
	if (isCollisionDetectionWithOpp(vir_pl[0], vir_pl[1])) {
		player[0].setAcceleration(player[1].getAccelerationX()*-1, player[1].getAccelerationY()*-1);
		player[1].setAcceleration(player[0].getAccelerationX()*-1, player[0].getAccelerationY()*-1);
	}

#endif
}


Point Collision::findAdjustmentCoord(std::string key, Rect a, int wr,int hr)
{
	Point e(0.0, 0.0);
	if (key == "Up") {
		e.y = a.h + hr;
	}
	if (key == "Bottom") {
		e.y = a.y - hr;
	}
	if (key == "Left") {
		e.x = a.w + wr;
	}
	if (key == "Right") {
		e.x = a.x - wr;
	}
	return e;
}

Point Collision::findAdjustmentCoordOpp(std::string key, Ellipse a, int wr, int hr)
{
	Point e(0.0, 0.0);
	if (key == "Up") {
		e.y = a.y + hr;
	}
	if (key == "Down") {
		e.y = a.y - hr;
	}
	if (key == "Left") {
		e.x = a.y + wr;
	}
	if (key == "Right") {
		e.x = a.x - wr;
	}
	return e;
}

void Collision::redistributedAcceleration(Player* & _p1, Player* & _p2)
{
	bool _isAccerelationXVaild = false;

	double _acceX1 = _p1->getAccelerationX();
	double _acceY1 = _p1->getAccelerationY();
	double _acceX2 = _p2->getAccelerationX();
	double _acceY2 = _p2->getAccelerationY();

	_p1->setAcceleration( _acceX2, _acceY2);
	_p2->setAcceleration(_acceX1, _acceY1);
	

	
#if 0
//	if (!_isTmpFull) {
		double _conversationQuantityX = -_p1->getAccelerationX();
		double _conversationQuantityY = -_p1->getAccelerationY();

		_conversationQuantityX -= _p2->getAccelerationX();
		_conversationQuantityY -= _p2->getAccelerationY();

		_acceXtmp = -_p1->getAccelerationX();
		_acceYtmp = -_p1->getAccelerationY();

		_p1->setAcceleration(-_conversationQuantityX, -_conversationQuantityY);
		_isTmpFull = true;
//	}
//	else {
		_p2->setAcceleration(_acceXtmp, _acceYtmp);
		_isTmpFull = false;
//	}
#endif
#if 0
	double _acceX = _p1->getAccelerationX();
	double _acceY = _p1->getAccelerationY();

	_p1->setAcceleration(-_p2->getAccelerationX(), -_p2->getAccelerationY());
	_p2->setAcceleration(-_acceX, -_acceY);

#endif

#if 0

	std::string _direction1 = _p1->getMovingDirection();
	std::string _direction2 = _p2->getMovingDirection();


	if (discernedWinningAcceleration(_p1, _p2, _isAccerelationXVaild)) {
		if (_direction1 == "right" || _direction1 == "left") {
			_conversationQuantityX = -_p2->getAccelerationX();
		}
		else if (_direction1 == "up" || _direction1 == "right") {
			_conversationQuantityY = -_p2->getAccelerationY();
		}
	}
	else {
		if (_direction1 == "right" || _direction1 == "left") {
			_conversationQuantityX = -_p2->getAccelerationX();//*= -1.5;
		}
		else if (_direction1 == "up" || _direction1 == "right") {
			_conversationQuantityY = -_p2->getAccelerationY();//*= -1.5;
		}
	}

	if (_direction1 == "right" || _direction1 == "left") {
		_conversationQuantityX = -_p2->getAccelerationX();
	}
	else if (_direction1 == "up" || _direction1 == "right") {
		_conversationQuantityY = -_p2->getAccelerationY();
	}

	_p1->setAcceleration(_conversationQuantityX,_conversationQuantityY);

#endif
}

bool Collision::discernedWinningAcceleration(Player* _p1,Player* _p2, bool& isAcceXValid)
{
	double _acceX1 = abs(_p1->getAccelerationX());// *(_p1->getAccelerationX() < 0.0 ? -1 : 1);
	double _acceY1 = abs(_p1->getAccelerationY());// *(_p1->getAccelerationY() < 0.0 ? -1 : 1);
	double _acceX2 = abs(_p2->getAccelerationX());// *(_p2->getAccelerationX() < 0.0 ? -1 : 1);
	double _acceY2 = abs(_p2->getAccelerationY());// *(_p2->getAccelerationY() < 0.0 ? -1 : 1);

	isAcceXValid = (_acceX1 != 0.0 ? true : false);
	bool isAcceX2Valid = (_acceX2 != 0.0 ? true : false);

	if ((isAcceXValid&&isAcceX2Valid&&_acceX1 > _acceX2) ||
		(isAcceXValid&&!isAcceX2Valid&&_acceX1 > _acceY2) ||
		(!isAcceXValid&&isAcceX2Valid&&_acceY1 > _acceX2) ||
		(!isAcceXValid&&!isAcceX2Valid&&_acceY1 > _acceY2)
		) {
		return true;
	}


	return false;
}

