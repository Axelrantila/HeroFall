#include "AudioMixer.h"
#include "EnemyTroll.h"
#include "LevelObjectRectangle.h"
#include "SpriteSheetLoader.h"

#include <iostream>

EnemyTroll::EnemyTroll(float xPos, float yPos)
	:Enemy(ENEMY_TROLL, xPos, yPos, SettingsManager::getSettings()->ENEMY_TROLL_HEALTH)
{
	m_sprite = SpriteSheetLoader::getInstance()->getSprite("Troll", "Troll_Walk_0_0");
	m_sprite->setPosition(xPos, yPos);

	m_yVel = 0.0f;
	m_xVel = -125.0f;

	m_animations = new AnimationManager(this);
	m_animations->addAnimation("Troll_Walk_0", 1.0f, m_xPos, m_yPos);
	m_animations->addAnimation("Troll_Hit_0", 0.1f, m_xPos, m_yPos);
	m_animations->setCurrentAnimation("Troll_Walk_0");

	m_hitted = false;
	m_meleeHitTime = SettingsManager::getSettings()->ENEMY_TROLL_HIT_TIME_LIMIT_MELEE;
	m_hitClock.restart();
}


EnemyTroll::~EnemyTroll()
{
	delete m_animations;
	delete m_sprite;
}

void EnemyTroll::update(float delta)
{
	m_sprite->setPosition(m_xPos, m_yPos);
	m_animations->update(m_xPos, m_yPos);

	if(m_hitClock.getElapsedTime().asSeconds() >= m_meleeHitTime && m_hitted)
	{
		m_hitted  = false;
		m_animations->setCurrentAnimation("Troll_Walk_0");
	}
}

void EnemyTroll::draw(sf::RenderWindow* window)
{
	//window->draw(*m_sprite);
	window->draw(*m_animations->getCurrentSprite());
}

sf::FloatRect EnemyTroll::getGlobalBounds()
{
	return m_animations->getCurrentSprite()->getGlobalBounds();
}

bool EnemyTroll::collidesWith(LevelObject* levelObject)
{
	if(levelObject->getLevelObjectType() == LO_RECTANGLE)
	{
		sf::Vector2f otherSize = ((LevelObjectRectangle*)levelObject)->getSize();
		float otherXPos = ((LevelObjectRectangle*)levelObject)->getXPos();
		float otherYPos = ((LevelObjectRectangle*)levelObject)->getYPos();

		return(!(otherXPos > getXPos() + m_sprite->getGlobalBounds().width
			|| otherXPos + otherSize.x < getXPos()
			|| otherYPos > getYPos() + m_sprite->getGlobalBounds().height
			|| otherYPos + otherSize.y < getYPos()));
	}

	return false;
}

void EnemyTroll::takeDamage(float damage)
{
	if(m_hitClock.getElapsedTime().asSeconds() > m_meleeHitTime)
	{
		m_hitClock.restart();
		m_health -= damage;
		m_animations->setCurrentAnimation("Troll_Hit_0");

		m_hitted = true;

		AudioMixer::getInstance()->playSound("Attack_hit_1", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 10.0f, 0.0f, 1.0f);

		//Check if character is dead
		if(m_health <= 0.0f)
		{m_isDead = true;}
	}
}