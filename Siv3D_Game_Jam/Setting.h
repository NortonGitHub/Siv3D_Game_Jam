#pragma once
#include "SceneBase.h"
#include "KeyBase.h"
#include "SettingBase.h"

class Setting :
	public SceneBase,
	SettingBase
{
public:
	Setting();
	~Setting();

	SceneBase* update() override;
	void draw() override;

private:
	enum Scene {
		MODE_SELECT,PARTICIPATE
	};

	KeyBase _key;
	Triangle selectingIcon;

	std::vector<PARTICIPANT> participant;

	Font topMessageFont;
	Font centerMessageFont;
	Font playerStatusFont;
	Rect frames[4];

	enum Scene _nowScene;

	enum GAME_MODE _gameMode;

	SceneBase* updateModeSelect();
	SceneBase* updateParticipate();

	void drawModeSelect();
	void drawParticipate();
};

