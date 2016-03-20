#include "Player.h"



Player::Player(int n, int all_player)
	:font(30),
	half_of_width(Window::Width()/2),
	initialCoord{ Vec2(52,82),Vec2(580,82),Vec2(52,380),Vec2(580,380) },
	indicatingHPCoord{ Vec2(half_of_width - 210,410),Vec2(half_of_width - 90,410),Vec2{half_of_width + 30,410},Vec2{half_of_width+150,410} },
	usingpad(n-1)
{
	_wr = 40;
	_hr = 60;

	_hp = 100;

	_accelerationX = 0.0;
	_accelerationY = 0.0;

	color = Palette::White;

	frame = 0;

	initPlayer(n);
	allPlayerVal = all_player;

	_direction = "stop";

	yolk.r = Body.axis.x;
	_isBrokenCompleted = false;

	indicatingHP.setSize(Vec2(60, 90));
	indicatingHP.setPos(indicatingHPCoord[n - 1]);
}

void Player::initPlayer(int n)
{
	num = n;
	/*
	_x = (num == 1) ? 52 : 580;
	_y = (num == 1) ? 380 : 82;
	*/

	_x = initialCoord[n - 1].x;
	_y = initialCoord[n - 1].y;

	Body.set(_x, _y, _wr / 2, _hr / 2);

}

void Player::initBroken()
{
	yolk.center = Body.center;
	color = Palette::Yellow;
	for (std::array<Triangle, 4>::iterator it = eggShell.begin(); it != eggShell.end(); it++) {
		int _angle = Random(360);
		double _x = yolk.center.x + (cos(_angle) * 20);
		double _y = yolk.center.y + (sin(_angle) * 20);
		it->setCentroid(_x, _y);
		it->set(_x, _y - Random(5, 10), _x - Random(5, 10), _y + Random(5, 10), _x + Random(5, 10), _y + Random(5, 10));
		it->rotated(Random(180));
	}
	_isBrokenCompleted = true;
}

bool Player::isHPFallBelowZERO()
{
	if (_hp <= 0) {
		return true;
	}
	return false;
}


Player::~Player()
{
}

Player* Player::update()
{
	updateResistance();

	_x += _accelerationX;
	_y += _accelerationY;

	setMovingDirection();

	Body.x = _x;
	Body.y = _y;

	if (isHPFallBelowZERO()) {
		if(!_isBrokenCompleted)
			initBroken();
		return this;
	}

	KeyBase::inputKey(_accelerationX, _accelerationY, usingpad, _direction);

	rollDirection();

	effects.update();


	if (frame >= 1000) {
		frame = 0;
	}
	++frame;

	return this;
}

void Player::draw()
{
	(!isHPFallBelowZERO()) ? drawNormal() : drawBroken();
}

void Player::drawNormal()
{
	Body.draw(color);

	effects.draw();

	font(L"‰Á‘¬“x", _accelerationX, L"HP", _hp).draw(20.0, 32.0*num);
}

void Player::drawBroken()
{
	yolk.draw(color);
	for (auto es : eggShell) {
		es.draw(Palette::Whitesmoke);
	}
}

void Player::setAcceleration(double _x, double _y)
{
	_accelerationX = _x;
	_accelerationY = _y;
	
}

void Player::setEffectsInit(Point oponentAcce, Vec2 myCenter)
{
	effects.init(oponentAcce, myCenter, _direction);
}

void Player::updateResistance()
{
	if (_accelerationX != 0.0) {
		if (_accelerationX < 0) {
			_accelerationX += 0.2;
		}
		else {
			_accelerationX -= 0.2;
		}
	}

	if (_accelerationX<0.2&& _accelerationX>-0.2) {
		_accelerationX = 0.0;
	}
	
	if (_accelerationY != 0.0) {
		if (_accelerationY < 0) {
			_accelerationY += 0.2;
		}
		else {
			_accelerationY -= 0.2;
		}
	}

	if (_accelerationY<0.2&& _accelerationY>-0.2) {
		_accelerationY = 0.0;
	}
}

void Player::rollDirection()
{
	
	if (_accelerationY != 0.0) {
		graPeriod = fmod(graPeriod + 20, 360.0);
		double rad = Radians(graPeriod);
		double size = cos(rad);

		double a = (_hr / 2) - size*4;

		Body.setSize(_wr / 2, a);
	}
	else if (_accelerationX != 0.0) {
		graPeriod = fmod(graPeriod + 45, 360.0);
		double rad = Radians(graPeriod);
		double bi = sin(rad);

		Body.y += bi;

	}
}

void Player::setMovingDirection()
{
	if (_accelerationX > 0.0) {
		_direction = "right";
	}
	else if (_accelerationX < 0.0) {
		_direction = "left";
	}
	else if (_accelerationY > 0.0) {
		_direction = "down";
	}
	else if (_accelerationY < 0.0) {
		_direction = "up";
	}
	else {
		_direction = "stop";
	}
}

void Player::reflectingDamageToHP(Point opponent)
{
	double _acceSum1 = abs(_accelerationX + _accelerationY);
	double _acceSum2 = abs(opponent.x + opponent.y);


	double _damage = (_acceSum1 > _acceSum2) ? _acceSum2 / 2 : _acceSum2 * 1.5;
	_hp -= _damage;
}

void Player::reflectingDamageToHPWithWall()
{
	double _acceSum = abs(_accelerationX + _accelerationY);

	double _damage = _acceSum;
	_hp -= _damage;
}
