#ifndef SWORDBEHAVIORFIRERUSG_H
#define SWORDBEHAVIORFIRERUSG_H

#include "SwordBehavior.h"

class SwordBehaviorFireRush
	:public SwordBehavior
{
public:
	SwordBehaviorFireRush(sf::Sprite* targetSprite, float totalTime);
	~SwordBehaviorFireRush();
};

#endif