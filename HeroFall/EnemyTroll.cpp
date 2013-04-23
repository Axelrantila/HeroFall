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
}


EnemyTroll::~EnemyTroll()
{
}

void EnemyTroll::update(float delta)
{
	m_sprite->setPosition(m_xPos, m_yPos);
}

void EnemyTroll::draw(sf::RenderWindow* window)
{
	window->draw(*m_sprite);
}

sf::FloatRect EnemyTroll::getGlobalBounds()
{
	return m_sprite->getGlobalBounds();
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