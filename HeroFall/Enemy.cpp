#include "Enemy.h"
#include "LevelObjectRectangle.h"
#include "SettingsManager.h"

Enemy::Enemy(EnemyType type, float xPos, float yPos, float health, sf::View* view)
	:Character(PT_UPPER_LEFT, xPos, yPos, health)
{
	m_type = type;
	m_health = health;
	m_view = view;
	m_seen = false;
}


Enemy::~Enemy()
{
}

void Enemy::move(float delta, std::vector<LevelObject*> levelObjects)
{
	m_yVel += getGravityDistance(delta);
	float yMove = delta * m_yVel;

	m_yPos += yMove;
	for(unsigned int a = 0; a < levelObjects.size(); a++)
	{
		if(collidesWith(levelObjects[a]))
		{
			m_yPos -= yMove;
			m_yVel = 0.0f;
			break;
		}
	}

	float xMove = delta * m_xVel;
	m_xPos += xMove;
	for(unsigned int a = 0; a < levelObjects.size(); a++)
	{
		if(collidesWith(levelObjects[a]))
		{
			m_xPos -= xMove;
			m_xVel = 0.0f;
			break;
		}
	}
}

void Enemy::applyGravity(float delta)
{
	m_yVel += SettingsManager::getSettings()->WORLD_GRAVITY * delta;
}

float Enemy::getGravityDistance(float delta)
{
	return SettingsManager::getSettings()->WORLD_GRAVITY * delta;
}