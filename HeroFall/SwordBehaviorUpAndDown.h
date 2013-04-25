#ifndef SWORDBEHAVIORUPANDDOWN_H
#define SWORDBEHAVIORUPANDDOWN_H

#include "SwordBehavior.h"

class SwordBehaviorUpAndDown
	:public SwordBehavior
{
public:
	SwordBehaviorUpAndDown(sf::Sprite* targetSprite, float totalTime);
	~SwordBehaviorUpAndDown();

	void update();
};

#endif