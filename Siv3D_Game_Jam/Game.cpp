#include "Game.h"
#include "Collision.h"
#include "Over.h"

Game::Game() {

}

Game::Game(int player_val, std::array<int, 4> participant)
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
#if 1
	for (int i = 0; i < player_val; i++) {
		player.push_back(new Player(participant[i],player_val));
		_hpUI.push_back(i);
	}
	
#endif

}


Game::~Game()
{
}

SceneBase* Game::update()
{
	Ellipse vir_pl[2];

	Collision::CollisionDetection(player, enclosures);

	int nowAllivingNum = 0;

	for (std::vector<Player*>::iterator p = player.begin(); p != player.end(); p++) {
		if (*p == nullptr)
			continue;

		*p = (*p)->update();

		std::iterator_traits<std::vector<int>::iterator>::difference_type index = p - player.begin();
		_hpUI[index].setPlayerHP((*p)->getHP());
		
		if (!(*p)->isHPFallBelowZERO())
			nowAllivingNum++;
	}

	if (nowAllivingNum <= 1) {
		return new Over(nowAllivingNum);
	}

#if 1
	for (std::vector<PlayerStatus>::iterator it = _hpUI.begin(); it != _hpUI.end();it++) {
		it->update(player);
	}
#endif
	
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

#if 0
	for (std::vector<PlayerStatus>::iterator it = _hpUI.begin(); it != _hpUI.end(); it++) {
		for (std::vector<Player*>::iterator p = player.begin(); p != player.end(); p++) {
			it->draw((*p)->getHP(), (*p)->getEllipseBody());
		}
	}
#endif

	for (std::map<std::string, Enclosure*>::iterator it = enclosures.begin(); it != enclosures.end(); it++) {
		it->second->draw();
	}

	for (auto u : _hpUI) {
		u.draw();
	}
}