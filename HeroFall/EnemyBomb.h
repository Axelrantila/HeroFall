#ifndef ENEMYBOMB_H
#define ENEMYBOMB_H

#include "Enemy.h"

class EnemyGoblin;

class EnemyBomb
	:public Enemy
{
public:
	EnemyBomb(float xPos, float yPos, EnemyGoblin* parent);
	~EnemyBomb();

private:
	EnemyGoblin* m_parent;
};

#endif