#include "Title.h"
#include "Setting.h"


Title::Title()
	: font(18)
{
	_x = Window::Center().x;
	_y = Window::Center().y;
	tes = Circle(_x, _y, 20);

	_connectedVal = GamePadManager::countGamepadConnecting();
}


Title::~Title()
{
}

SceneBase* Title::update()
{
	for (int i = 0; i < _connectedVal; i++) {
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
	if (_connectedVal <= 2) {
		font(L"�\���Ȑ��̃Q�[���p�b�h��\n�ڑ�����Ă��܂���B\nESC�L�[�������ăQ�[������A\n�Q�[���p�b�h��ڑ����Ă���\n�ēx�Q�[�����J���Ă��������B").drawCenter(Window::Center(),Palette::Red);
	}
	tes.draw();
}
