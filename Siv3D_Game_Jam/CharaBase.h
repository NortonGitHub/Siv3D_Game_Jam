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

	double graPeriod;	//縦移動時の円の半径の変化時に使用
	double degree;		//横移動時のわずかな楕円の傾きに使用

};

