#include "Enemy.h"


Enemy::Enemy(EnemyType type, float xPos, float yPos, float health)
	:Character(PT_UPPER_LEFT, xPos, yPos, health)
{
	m_type = type;
}


Enemy::~Enemy()
{
}

void Enemy::move(float delta)
{
	//applyGravity(delta);
	m_xPos += delta * m_xVel;
	m_yPos += delta * m_yVel;
}

void Enemy::applyGravity(float delta)
{
	m_yVel += 100.0f * delta;
}

float Enemy::getGravityDistance(float delta)
{
	return 100.0f * delta;
}