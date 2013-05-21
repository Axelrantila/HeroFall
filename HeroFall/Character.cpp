#include "Character.h"
#include "SettingsManager.h"

Character::Character(PositionType positionType, float xPos, float yPos, float health)
	:GameObject(positionType, xPos, yPos)
{
	m_gravityConstant = 0.0f;
	m_xVel = 0.0f;
	m_yVel = 0.0f;
	m_armor = 0.0f;

	m_health = health;
	m_isDead = false;
	m_isDying = false;
	m_deathTime = 1.0f;

	m_direction = DIR_LEFT;
}


Character::~Character()
{
}

void Character::move(float delta)
{
	//applyGravity(delta);
	m_xPos += delta * m_xVel;
	m_yPos += delta * m_yVel;
}

void Character::applyGravity(float delta)
{
	m_yVel += SettingsManager::getSettings()->WORLD_GRAVITY * delta;
}

float Character::getGravityDistance(float delta)
{
	return SettingsManager::getSettings()->WORLD_GRAVITY * delta;
}

void Character::takeDamage(float damage)
{
	//Armor reduction

	//Deal damage
	m_health -= damage;

	//Check if character is dead
	if(m_health <= 0.0f)
	{m_isDying = true;}
}