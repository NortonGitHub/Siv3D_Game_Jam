#include "EffectManager.h"



EffectManager::EffectManager()
{
}


EffectManager::~EffectManager()
{
}

void EffectManager::init(Point oponentAcce, Vec2 myCenter, std::string direction)
{
	int xy = abs(oponentAcce.x + oponentAcce.y);
	Vec2 sumCenter = myCenter + Vec2(oponentAcce);
	
	for (int i = 0; i < _effectStar.size(); i++) {
		_effectStar[i] = (_effectStar[i] == nullptr) ? new Star(sumCenter, direction) : nullptr;
	}
}

void EffectManager::update()
{
	for (int i = 0; i < _effectStar.size(); i++) {
		if (_effectStar[i] != nullptr) {
			_effectStar[i] = _effectStar[i]->update();
		}
	}
}

void EffectManager::draw()
{
	for (int i = 0; i < _effectStar.size(); i++) {
		if (_effectStar[i] != nullptr) {
			_effectStar[i]->draw();
		}
	}
}
