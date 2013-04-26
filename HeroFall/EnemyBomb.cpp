#include "EnemyBomb.h"


EnemyBomb::EnemyBomb(float xPos, float yPos, EnemyGoblin* parent)
	:Enemy(ENEMY_BOMB, xPos, yPos, 1.0f)
{
	m_parent = parent;
}


EnemyBomb::~EnemyBomb()
{
}
