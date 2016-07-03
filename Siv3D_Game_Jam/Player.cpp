#include "Player.h"
#include "Collision.h"


Player::Player(int padNum, int orderNum, int all_player)
	:font(30),
	half_of_width(Window::Width()/2),
	initialCoord{ Vec2(52,82),Vec2(580,82),Vec2(52,380),Vec2(580,380) },
	usingpad(padNum - 1),
	orderNum(orderNum)
{

	color = selectBodyColor(orderNum);
	_wr = 40;
	_hr = 60;

	_hp = 100;

	playerNum = padNum - 1;

	_accelerationX = 0.0;
	_accelerationY = 0.0;

	frame = 0;

	initPlayer(orderNum);
	allPlayerVal = all_player;

	_direction = "stop";

	yolk.r = Body.axis.x;
	_isBrokenCompleted = false;
}

void Player::initPlayer(int n)
{

	_x = initialCoord[n].x;
	_y = initialCoord[n].y;

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

	Body.x = _x;
	Body.y = _y;

	if (isHPFallBelowZERO()) {
		if(!_isBrokenCompleted)
			initBroken();
		return this;
	}

	KeyBase::inputKey(_accelerationX, _accelerationY, usingpad);

	setMovingDirection();

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


	String a = Widen(_direction);
//	font(L"direction", a).draw(40.0, 60.0*orderNum, color);
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
	if (_direction == "Stop")
		return;

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
		_direction = "Right";
	}
	else if (_accelerationX < 0.0) {
		_direction = "Left";
	}
	else if (_accelerationY > 0.0) {
		_direction = "Down";
	}
	else if (_accelerationY < 0.0) {
		_direction = "Up";
	}
	else {
		_direction = "Stop";
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
