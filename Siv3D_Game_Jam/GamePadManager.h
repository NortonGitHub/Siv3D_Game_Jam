#pragma once
#include <vector>
#include "SettingBase.h"

class GamePadManager:
	 public SettingBase
{
public:
	GamePadManager();
	~GamePadManager();

	static int countGamepadConnecting();
	static bool isClickedAnyButton(int pad_num);
	static bool isPressedAnyButton(int pad_num);
	static bool isAllPadPressed(std::vector<PARTICIPANT> participant);
};

