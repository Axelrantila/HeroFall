#include "EnemyPlaceholder.h"
#include "InputManager.h"
#include "LevelObjectRectangle.h"
#include "Player.h"
#include "SpriteSheetLoader.h"

#include <iostream>
#include <math.h>

Player::Player(float xPos, float yPos)
	:Character(PT_UPPER_LEFT, xPos, yPos, 125.0f)
{
	m_swordIsSwinging = false;
	m_swordHasHittedEnemy = true;
	m_targetSwingTime = 0.5f;

	m_rect = SpriteSheetLoader::getInstance()->getSprite("Avatar", "Avatar_0");
	m_rect->setPosition(100.0f, 100.0f);
	m_rect->setScale(0.2f, 0.2f);

	m_swordRect = SpriteSheetLoader::getInstance()->getSprite("Avatar", "Avatar_Sword");
	m_swordRect->setOrigin(0.0f, 273.5f);
	m_swordRect->setScale(0.2f, 0.2f);
	m_swordRect->setPosition(m_rect->getGlobalBounds().left  + m_rect->getGlobalBounds().width * 0.5f,
		m_rect->getGlobalBounds().top + m_rect->getGlobalBounds().height * 0.5f);

	m_xVel = 0.0f;
	m_yVel = 0.0f;

	d_testAnim = new Animation(this, "Turt_Attack_0", 0.5f, 200.0f, 200.0f);
	d_testAnim->play();
}


Player::~Player()
{
	delete m_rect;
	delete m_swordRect;

	delete d_testAnim;
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(*m_rect);
	window->draw(*m_swordRect);
	d_testAnim->update(200.0f, 200.0f);
	window->draw(*d_testAnim->getCurrentSprite());
}

void Player::move(float delta, std::vector<LevelObject*> levelObjects)
{
	m_yVel += getGravityDistance(delta);
	float m_xMove = delta * m_xVel;
	float m_yMove = delta * m_yVel;

	m_xPos += m_xMove;
	for(unsigned int a = 0; a < levelObjects.size(); a++)
	{
		if(collidesWith(levelObjects[a]))
		{
			m_xPos -= m_xMove;
			m_xVel = 0.0f;
			break;
		}
	}

	m_yPos += m_yMove;
	for(unsigned int a = 0; a < levelObjects.size(); a++)
	{
		if(collidesWith(levelObjects[a]))
		{
			m_yPos -= m_yMove;
			m_yVel = 0.0f;
			break;
		}
	}

	m_rect->setPosition(m_xPos, m_yPos);
	m_swordRect->setPosition(m_rect->getGlobalBounds().left  + m_rect->getGlobalBounds().width * 0.5f,
		m_rect->getGlobalBounds().top + m_rect->getGlobalBounds().height * 0.5f);
}

void Player::increaseSpeed(float xVel, float yVel)
{
	m_xVel += xVel;
	m_yVel += yVel;
}

bool Player::collidesWith(LevelObject* levelObject)
{
	if(levelObject->getLevelObjectType() == LO_RECTANGLE)
	{
		sf::Vector2f otherSize = ((LevelObjectRectangle*)levelObject)->getSize();
		float otherXPos = ((LevelObjectRectangle*)levelObject)->getXPos();
		float otherYPos = ((LevelObjectRectangle*)levelObject)->getYPos();

		return(!(otherXPos > getXPos() + m_rect->getGlobalBounds().width
			|| otherXPos + otherSize.x < getXPos()
			|| otherYPos > getYPos() + m_rect->getGlobalBounds().height
			|| otherYPos + otherSize.y < getYPos()));
	}

	return false;
}

void Player::collidesWith(std::vector<Enemy*>* enemies)
{
	for(unsigned int a = 0; a < enemies->size();)
	{
		if(enemies->at(a)->getType() == ENEMY_PLACEHOLDER)
		{
			EnemyPlaceholder* tEnemy = ((EnemyPlaceholder*)enemies->at(a));
			if(m_swordRect->getGlobalBounds().intersects(tEnemy->getRect()->getGlobalBounds())
				&& m_swordIsSwinging
				&& !m_swordHasHittedEnemy)
			{
				enemies->at(a)->takeDamage(50.0f);
				m_swordHasHittedEnemy = true;
			}

			if(m_rect->getGlobalBounds().intersects(tEnemy->getRect()->getGlobalBounds()))
			{
				this->takeDamage(60.0f);
			}
		}
		
		//Delete any dead enemies
		if(enemies->at(a)->isDead())
		{
			delete enemies->at(a);
			enemies->erase(enemies->begin() + a);
		}
		else
		{
			a++;
		}
	}
}

sf::Vector2f Player::getCenter()
{
	return sf::Vector2f(m_xPos + m_rect->getGlobalBounds().width/2.0f,
		m_yPos + m_rect->getGlobalBounds().height/2.0f);
}

void Player::swingSword()
{
	m_swordIsSwinging = true;
	m_swordHasHittedEnemy = false;
	m_swordClock.restart();
}

void Player::update(float delta)
{
	if(InputManager::getInstance()->isKeyDown("P1_ATTACK_1") && !m_swordIsSwinging)
	{
		swingSword();
	}

	if(m_swordIsSwinging)
	{
		m_swordRect->setRotation((m_swordClock.getElapsedTime().asSeconds() / m_targetSwingTime) * 360.0f);

		if(m_swordClock.getElapsedTime().asSeconds() >= m_targetSwingTime)
		{
			m_swordRect->setRotation(0.0f);
			m_swordIsSwinging = false;
		}
	}
} 

void Player::setXSpeed(float xVel)
{
	m_xVel = xVel;
}