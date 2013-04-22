#ifndef ENEMYSHOOTER_H
#define ENEMYSHOOTER_H

#include "Enemy.h"

class EnemyShooter :
	public Enemy
{
public:
	EnemyShooter(float xPos, float yPos, float health);
	~EnemyShooter();
};

#endif 