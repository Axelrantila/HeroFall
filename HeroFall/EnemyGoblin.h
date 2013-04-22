#ifndef ENEMYGOBLIN_H
#define ENEMYGOBLIN_H

#include "Enemy.h"

class EnemyGoblin
	:public Enemy
{
public:
	EnemyGoblin(float xPos, float yPos, float health);
	~EnemyGoblin();
};

#endif