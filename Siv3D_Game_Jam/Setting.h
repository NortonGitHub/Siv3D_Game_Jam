#pragma once
#include "SceneBase.h"
#include "KeyBase.h"

class Setting :
	public SceneBase
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

	struct PARTICIPANT{
		int num;
		bool hasParticipate;
	};

	KeyBase _key;
	Triangle selectingIcon;

	std::array<PARTICIPANT, 4> participant;
	int participantVal;

	Font topMessageFont;
	Font centerMessageFont;
	Font playerStatusFont;
	Rect frames[4];

	enum Scene _nowScene;

	SceneBase* updateModeSelect();
	SceneBase* updateParticipate();

	void drawModeSelect();
	void drawParticipate();
};

