#include "GamePadManager.h"
#include <Siv3D.hpp>


GamePadManager::GamePadManager()
{
}


GamePadManager::~GamePadManager()
{
}

int GamePadManager::countGamepadConnecting()
{
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (Gamepad(i).isConnected()) {
			count++;
		}
	}
	
	return count;
}

bool GamePadManager::isClickedAnyButton(int pad_num)
{
	for (int j = 0; j < Gamepad(pad_num).num_buttons; j++) {
		if (Gamepad(pad_num).button(j).clicked) {
			return true;
		}
	}
	return false;
}

bool GamePadManager::isPressedAnyButton(int pad_num)
{
	for (int j = 0; j < Gamepad(pad_num).num_buttons; j++) {
		if (Gamepad(pad_num).button(j).pressed) {
			return true;
		}
	}
	return false;
}

bool GamePadManager::isAllPadPressed(int all_pad_val)
{
	int clear = 0;
	for (int i = 0; i < all_pad_val;i++){
		for (int j = 0; j < Gamepad(i).num_buttons; j++) {
			if (Gamepad(i).button(j).pressed) {
				clear++;
			}
		}
	}
	return (clear >= all_pad_val) ? true : false;
}
