#include <memory>
#include "Game.h"
#include "Collision.h"
#include "Over.h"

Game::Game() {

}

Game::Game(int player_val, std::array<int, 4> participant,GAME_MODE _gameMode)
{
	
	enclosures.insert(std::map<std::string, Enclosure*>::value_type("Up", new Enclosure(0, 0, 640, 30, Palette::Aqua)));			//Uppper
	enclosures.insert(std::map<std::string, Enclosure*>::value_type("Bottom", new Enclosure(0, 450, 640, 30, Palette::Aqua)));		//Bottom
	enclosures.insert(std::map<std::string, Enclosure*>::value_type("Left", new Enclosure(0, 0, 30, 480, Palette::Aqua)));			//left
	enclosures.insert(std::map<std::string, Enclosure*>::value_type("Right", new Enclosure(610, 0, 30, 480, Palette::Aqua)));		//right
	enclosures.insert(std::map<std::string, Enclosure*>::value_type("UL", new Enclosure(0, 0, 30, 30, Palette::Aquamarine)));		//Upper-left corner
	enclosures.insert(std::map<std::string, Enclosure*>::value_type("UR", new Enclosure(610, 0, 30, 30, Palette::Aquamarine)));		//Upper-right corner
	enclosures.insert(std::map<std::string, Enclosure*>::value_type("BL", new Enclosure(0, 450, 30, 30, Palette::Aquamarine)));		//Bottom-left corner
	enclosures.insert(std::map<std::string, Enclosure*>::value_type("BR", new Enclosure(610, 450, 30, 30, Palette::Aquamarine)));	//Bottom-right corner
	_hpUI.reserve(4);

	_participant = participant;

	_nowGameMode = _gameMode;

#if 1
	for (int i = 0; i < player_val; i++) {
		player.push_back(new Player(_participant[i], player_val, _gameMode));
		_hpUI.push_back(i);
	}
	
	_gameResult = nullptr;
#endif
}


Game::~Game()
{
}

void Game::initGame()
{
	for (int i = 0; i < _participant.size(); i++) {
		player[i]->initPlayer(_participant[i], _nowGameMode);
	}
	
	_nowAllivingNum = player.size();
	_gameResult = nullptr;
	_limitedTime.restart();
}

bool Game::isSatisfiedClearCondition()
{
	switch (_nowGameMode) {
	case DEATHMATCH:
		if (_nowAllivingNum <= 1)
			return true;
		break;
	default:
		if (_limitedTime.ms() >= 30000)
			return true;
	}
	return false;
}

SceneBase* Game::update()
{
	return (_gameResult == nullptr) ? updateNormal() : updateResult();
}

SceneBase * Game::updateNormal()
{
	Ellipse vir_pl[2];
	std::vector<int> processed;

	//Collision::CollisionDetection(player, enclosures, _nowGameMode);

	for (std::vector<Player*>::iterator p = player.begin(); p != player.end(); p++) {
		
		if ((*p)->isHPFallBelowZERO())
			continue;

		/*“–‚½‚è”»’è*/
		for (auto e : enclosures) {
			if (Collision::isCollisionDetection((*p)->getEllipseBody(), e.second->wall)) {
				(*p)->getEllipseBody().setPos(Collision::findAdjustmentCoord(e.first, e.second->wall, (*p)->getWidthRadius() / 2, (*p)->getHeightRadius() / 2));
				(*p)->setAcceleration((*p)->getAccelerationX()*-1, (*p)->getAccelerationY()*-1);
			}
		}

		for (std::vector<Player*>::iterator p2 = player.begin(); p2 != player.end(); p2++) {
			if (p == p2 || std::find(processed.begin(),processed.end(),(*p)->getPlayerNum()*(*p2)->getPlayerNum()) != processed.end())
				continue;


			if (Collision::isCollisionDetectionWithOpp((*p)->getEllipseBody(), (*p2)->getEllipseBody())) {
				Point _acce1 = Point((*p)->getAccelerationX(), (*p)->getAccelerationY());
				Point _acce2 = Point((*p2)->getAccelerationX(), (*p2)->getAccelerationY());

				(*p)->setEffectsInit(_acce2, (*p)->getEllipseBody().center);
				(*p2)->setEffectsInit(_acce1, (*p)->getEllipseBody().center);

				(*p)->reflectingDamageToHP(_acce2,_nowGameMode);
				(*p2)->reflectingDamageToHP(_acce1,_nowGameMode);
				Collision::redistributedAcceleration(*p, *p2);
				processed.push_back((*p)->getPlayerNum() * (*p2)->getPlayerNum());
			}

		}
		/**/

		*p = (*p)->update();

		std::iterator_traits<std::vector<int>::iterator>::difference_type index = p - player.begin();
		_hpUI[index].setPlayerHP((*p)->getHP());
	}

	if (isSatisfiedClearCondition()) {
		delete(_gameResult);
		_gameResult = new GameResult(_nowAllivingNum, player);
	}

#if 1
	for (std::vector<PlayerStatus>::iterator it = _hpUI.begin(); it != _hpUI.end(); it++) {
		it->update(player);
	}
#endif

	processed.erase(processed.begin(), processed.end());

	return this;
}

SceneBase * Game::updateResult()
{
	if (_gameResult->update()) {
		return new Over();
	}

	return this;
}

void Game::draw()
{
	for (std::vector<Player*>::iterator p = player.begin(); p != player.end(); p++) {
		if (*p == nullptr)
			continue;

		(*p)->draw();

		std::iterator_traits<std::vector<int>::iterator>::difference_type index = p - player.begin();

	}
	
	for (std::map<std::string, Enclosure*>::iterator it = enclosures.begin(); it != enclosures.end(); it++) {
		it->second->draw();
	}

	for (auto u : _hpUI) {
		u.draw();
	}

	if (_gameResult != nullptr) {
		_gameResult->draw();
	}
}