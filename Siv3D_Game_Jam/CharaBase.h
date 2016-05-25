#pragma once
#include "VisualColorBase.h"

class CharaBase
	: protected VisualColorBase
{
public:
	CharaBase();
	~CharaBase();

	double getCoordX() {
		return _x;
	}
	double getCoordY() {
		return _y;
	}

protected:

	Image image;
	DynamicTexture texture;

	double _x;
	double _y;
	int _hr;
	int _wr;

	Color color;

	double _accelerationX;
	double _accelerationY;

	double graPeriod;	//cˆÚ“®‚Ì‰~‚Ì”¼Œa‚Ì•Ï‰»‚Ég—p
	double degree;		//‰¡ˆÚ“®‚Ì‚í‚¸‚©‚È‘È‰~‚ÌŒX‚«‚Ég—p

};

