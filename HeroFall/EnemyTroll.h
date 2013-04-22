#ifndef ENEMYTROLL_H
#define ENEMYTROLL_H

#include "Enemy.h"

class EnemyTroll
	:public Enemy
{
public:
	EnemyTroll(float xPos, float yPos, float health);
	~EnemyTroll();
};

#endif