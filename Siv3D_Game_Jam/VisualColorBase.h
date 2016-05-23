#pragma once
#include <Siv3D.hpp>
class VisualColorBase
{
public:
	VisualColorBase();
	~VisualColorBase();

protected:
	inline Color const VisualColorBase::selectBodyColor(int charactorNum)
	{
		using namespace Palette;


		switch (charactorNum) {
		case 0:
			return White;
		case 1:
			return Yellowgreen;
		case 2:
			return Lightblue;
		case 3:
			return Orangered;
		}
		return Gray;
	}

};

