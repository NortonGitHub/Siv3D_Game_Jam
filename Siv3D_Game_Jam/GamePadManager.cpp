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

bool GamePadManager::isAllPadPressed(std::vector<PARTICIPANT> participant)
{
	int clear = 0;

#if 1
	for (int i = 0; i < participant.size();i++){
		for (int j = 0; j < Gamepad(i).num_buttons; j++) {
			if (Gamepad(participant[i].num - 1).button(j).pressed) {
				clear++;
			}
		}
	}
#endif

	return (clear >= participant.size()) ? true : false;
}
