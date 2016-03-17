#pragma once
#include "SceneBase.h"

class Title :
	public SceneBase
{
public:
	Title();
	~Title();

	SceneBase* update() override;
	void draw() override;

private:
	int _connectedVal;
	Font font;
	Circle tes;
	double _x;
	double _y;
};

