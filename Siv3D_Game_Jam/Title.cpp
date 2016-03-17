#include "Title.h"
#include "Setting.h"


Title::Title()
	: font(18)
{
	_x = Window::Center().x;
	_y = Window::Center().y;
	tes = Circle(_x, _y, 20);
}


Title::~Title()
{
}

SceneBase* Title::update()
{
	_connectedVal = GamePadManager::countGamepadConnecting();

	for (int i = 0; i < 4; i++) {
		if (GamePadManager::isClickedAnyButton(i)) {
			return new Setting();
		}

#if 0	
		if (Gamepad(0).) {
			_x += 2;
		}

		tes.setPos(_x, _y);
#endif
	}

	return this;
}

void Title::draw()
{
	if (_connectedVal == 0) {
		font(L"ゲームパッドが接続されていません").drawCenter(Window::Center(),Palette::Red);
	}
	tes.draw();
}
