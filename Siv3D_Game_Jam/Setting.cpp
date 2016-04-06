#include "Setting.h"
#include "Game.h"


Setting::Setting()
	:topMessageFont(24),
	playerStatusFont(14),
	centerMessageFont(16)
{
	const int iconHeight = 40;
	const int iconWidth = 40;
	const Vec2 defaultPos(160, 80);
	selectingIcon = Triangle(defaultPos.x - iconWidth / 2, defaultPos.y - iconHeight / 2,
		defaultPos.x - iconWidth / 2, defaultPos.y + iconHeight / 2,
		defaultPos.x + iconWidth / 2, defaultPos.y);

	_nowScene = PARTICIPATE;

	participant.reserve(4);

	frames[0] = Rect(40, 120, 240, 140);
	frames[1] = Rect(360, 120, 240, 140);
	frames[2] = Rect(40, 300, 240, 140);
	frames[3] = Rect(360, 300, 240, 140);

	_gameMode = DEATHMATCH;
}


Setting::~Setting()
{
}

SceneBase* Setting::update() {

	return (_nowScene == MODE_SELECT) ? updateModeSelect() : updateParticipate();

	return this;
}

void Setting::draw() {
	return (_nowScene == MODE_SELECT) ? drawModeSelect() : drawParticipate();

}

SceneBase * Setting::updateModeSelect()
{
	double _movingX = 0.0;
	double _movingY = 0.0;

	std::string dammy;

	_key.inputKey(_movingX, _movingY, Gamepad(0), dammy);

	selectingIcon.setCentroid(_movingX * 20, _movingY * 20);

	if (Gamepad(0).button(1).pressed) {
		_nowScene = PARTICIPATE;
	}

	return this;
}

SceneBase * Setting::updateParticipate()
{
	int nowConnecting = GamePadManager::countGamepadConnecting();

	for (int i = 0; i < nowConnecting; i++) {
		if (GamePadManager::isClickedAnyButton(i)) {
			if (participant.size() > 3)
				break;

#if 0
			for (int j = 0; j < nowConnecting; j++) {
				if (participant[j].hasParticipate == true && participant[j].num == i + 1) {
					return this;
				}
			}
#endif
			auto itr = std::find(participant.begin(), participant.end(), PARTICIPANT{ i + 1 });

#if 1
			if (itr == participant.end()) {
				participant.push_back(PARTICIPANT{ i + 1 });
			}
#endif
		}
	}
	
	if (participant.size() >= 2 && GamePadManager::isAllPadPressed(participant)) {
		std::array<int, 4> temp;
		for (int i = 0; i < 4; i++) {
			if (i < participant.size())
				temp[i] = participant[i].num;
			else
				temp[i] = 0;
		}
		return new Game(participant.size(), temp, _gameMode);
	}

	return this;
}

void Setting::drawModeSelect()
{
	selectingIcon.draw(Palette::Aqua);
}

void Setting::drawParticipate()
{

	for (int i = 0; i < participant.size(); i++) {
		Circle(10 * i, 10, 5).draw(Palette::Green);
	}
	topMessageFont(L"参加者募集中!").drawCenter(Window::Width() / 2, 40.0, Palette::Aquamarine);

	for (int i = participant.size(); i < 4; i++) {
		frames[i].draw(Palette::Mediumblue);
		playerStatusFont(L"ボタンを押してください").drawCenter(frames[i].center);
	}

	for (int i = 0; i < participant.size(); i++) {
		frames[i].draw(Palette::Dodgerblue);
		playerStatusFont(L"player", participant[i].num).drawCenter(frames[i].center);
	}

	if (participant.size() >= 2) {
		centerMessageFont(L"ボタンを押し続けてスタート").drawCenter(Window::Center());
	}

}
