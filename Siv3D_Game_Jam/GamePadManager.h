#pragma once
class GamePadManager
{
public:
	GamePadManager();
	~GamePadManager();

	static int countGamepadConnecting();
	static bool isClickedAnyButton(int pad_num);
	static bool isPressedAnyButton(int pad_num);
	static bool isAllPadPressed(int all_pad_val);
};

