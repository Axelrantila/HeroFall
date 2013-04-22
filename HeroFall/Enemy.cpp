#include "Enemy.h"
#include "SettingsManager.h"

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
	/*
	UNFINISHED METOD!!!!!!!!!
	*/

	m_xPos += delta * m_xVel;
	m_yPos += delta * m_yVel;
}

void Enemy::move(float delta, std::vector<LevelObject*> levelObjects)
{
	/*
	UNFINISHED METOD!!!!!!!!!
	*/

	m_xPos += delta * m_xVel;
	m_yPos += delta * m_yVel;
}

void Enemy::applyGravity(float delta)
{
	m_yVel += SettingsManager::getSettings()->WORLD_GRAVITY * delta;
}

float Enemy::getGravityDistance(float delta)
{
	return SettingsManager::getSettings()->WORLD_GRAVITY * delta;
}