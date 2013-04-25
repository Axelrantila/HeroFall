#include "AudioMixer.h"
#include "EnemyPlaceholder.h"
#include "EnemyTroll.h"
#include "InputManager.h"
#include "LevelObjectRectangle.h"
#include "Player.h"
#include "SpriteSheetLoader.h"

#include <iostream>
#include <math.h>

Player::Player(float xPos, float yPos)
	:Character(PT_UPPER_LEFT, xPos, yPos, SettingsManager::getSettings()->PLAYER_HEALTH)
{
	m_swordIsSwinging = false;
	m_swordHasHittedEnemy = true;
	m_targetSwingTime = SettingsManager::getSettings()->PLAYER_SWORD_SWING_TIME;

	m_xVel = 0.0f;
	m_yVel = 0.0f;
	
	m_markedForHalt = false;

	m_meleeHitTime = SettingsManager::getSettings()->PLAYER_HIT_TIME_LIMIT_MELEE;
	m_meleeHitClock.restart();

	m_animations = new AnimationManager(this);
	m_animations->addAnimation("Hero_Hit_0", 0.1f, this->m_xPos, this->m_yPos);
	m_animations->addAnimation("Hero_Walk_0", 0.1f, this->m_xPos, this->m_yPos);
	m_animations->setCurrentAnimation("Hero_Walk_0");

	m_hitted = false;

	m_swordRect = SpriteSheetLoader::getInstance()->getSprite("Hero", "Hero_Sword_0_0");
	m_swordRect->setOrigin(0.0f, 96.0f);
	m_swordRect->setPosition(m_animations->getCurrentSprite()->getGlobalBounds().left  + m_animations->getCurrentSprite()->getGlobalBounds().width * 0.5f,
		m_animations->getCurrentSprite()->getGlobalBounds().top + m_animations->getCurrentSprite()->getGlobalBounds().height * 0.5f);
}

Player::~Player()
{
	delete m_animations->getCurrentSprite();
	delete m_swordRect;
	delete m_animations;
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(*m_animations->getCurrentSprite());
	window->draw(*m_swordRect);
}

void Player::move(float delta, std::vector<LevelObject*> levelObjects)
{
	m_yVel += getGravityDistance(delta);
	float m_yMove = delta * m_yVel;

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

	if(m_markedForHalt)
	{
		if(m_xVel > 0.0f)
		{
			m_xVel -= SettingsManager::getSettings()->PLAYER_SPEED_SIDE_HALTING * delta;
			if(m_xVel < 0.0f){m_xVel = 0.0f;}

			float m_xMove = delta * m_xVel;
			m_xPos += m_xMove;
			for(unsigned int a = 0; a < levelObjects.size(); a++)
			{
				if(collidesWith(levelObjects[a]))
				{
					std::cout << "Test2\n";
					m_xPos -= m_xMove;
					m_xVel = 0.0f;
					break;
				}
			}
		}
		else
		{
			m_xVel += SettingsManager::getSettings()->PLAYER_SPEED_SIDE_HALTING * delta;
			if(m_xVel > 0.0f){m_xVel = 0.0f;}

			float m_xMove = delta * m_xVel;
			m_xPos += m_xMove;
			for(unsigned int a = 0; a < levelObjects.size(); a++)
			{
				if(collidesWith(levelObjects[a]))
				{
					std::cout << "Test3\n";
					m_xPos -= m_xMove;
					m_xVel = 0.0f;
					break;
				}
			}
		}
	}
	else
	{
		float m_xMove = delta * m_xVel;
		m_xPos += m_xMove;
		for(unsigned int a = 0; a < levelObjects.size(); a++)
		{
			if(collidesWith(levelObjects[a]))
			{
				std::cout << "Test4\n";
				m_xPos -= m_xMove;
				m_xVel = 0.0f;
				break;
			}
		}
	}

	//m_animations->getCurrentSprite()->setPosition(m_xPos, m_yPos);
	m_animations->update(m_xPos, m_yPos);
	m_swordRect->setPosition(m_animations->getCurrentSprite()->getGlobalBounds().left  + m_animations->getCurrentSprite()->getGlobalBounds().width * 0.5f,
		m_animations->getCurrentSprite()->getGlobalBounds().top + m_animations->getCurrentSprite()->getGlobalBounds().height * 0.5f);
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

		return(!(otherXPos > m_xPos + m_animations->getCurrentSprite()->getGlobalBounds().width
			|| otherXPos + otherSize.x < m_xPos
			|| otherYPos > m_yPos + m_animations->getCurrentSprite()->getGlobalBounds().height
			|| otherYPos + otherSize.y < m_yPos));
	}

	return false;
}

void Player::collidesWith(std::vector<Enemy*>* enemies)
{
	for(unsigned int a = 0; a < enemies->size();)
	{
		//ENEMY PLACEHOLDER
		if(enemies->at(a)->getType() == ENEMY_PLACEHOLDER)
		{
			EnemyPlaceholder* tEnemy = ((EnemyPlaceholder*)enemies->at(a));
			if(m_swordRect->getGlobalBounds().intersects(tEnemy->getRect()->getGlobalBounds())
				&& m_swordIsSwinging
				&& !m_swordHasHittedEnemy)
			{
				enemies->at(a)->takeDamage(SettingsManager::getSettings()->DAMAGE_PLAYER_TO_ENEMY_PLACEHOLDER);
				m_swordHasHittedEnemy = true;
			}

			if(m_animations->getCurrentSprite()->getGlobalBounds().intersects(tEnemy->getRect()->getGlobalBounds()))
			{
				this->takeDamage(SettingsManager::getSettings()->DAMAGE_ENEMY_PLACEHOLDER_TO_PLAYER);
			}
		}

		//TROLL
		else if(enemies->at(a)->getType() == ENEMY_TROLL)
		{
			EnemyTroll* tEnemy = ((EnemyTroll*)enemies->at(a));
			if(m_swordRect->getGlobalBounds().intersects(tEnemy->getGlobalBounds())
				&& m_swordIsSwinging
				&& !m_swordHasHittedEnemy)
			{
				enemies->at(a)->takeDamage(SettingsManager::getSettings()->DAMAGE_PLAYER_TO_ENEMY_TROLL);
				m_swordHasHittedEnemy = true;
			}

			if(m_animations->getCurrentSprite()->getGlobalBounds().intersects(tEnemy->getGlobalBounds()))
			{
				this->takeDamage(SettingsManager::getSettings()->DAMAGE_ENEMY_TROLL_TO_PLAYER);
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
	return sf::Vector2f(m_xPos + m_animations->getCurrentSprite()->getGlobalBounds().width/2.0f,
		m_yPos + m_animations->getCurrentSprite()->getGlobalBounds().height/2.0f);
}

void Player::swingSword()
{
	m_swordIsSwinging = true;
	m_swordHasHittedEnemy = false;
	m_swordClock.restart();
	AudioMixer::getInstance()->playSound("Draw sword (skämt)");
}

void Player::update(float delta)
{
	if(InputManager::getInstance()->isKeyDown("P1_ATTACK_1") && !m_swordIsSwinging)
	{
		swingSword();
	}

	if(m_swordIsSwinging)
	{
		if(m_swordClock.getElapsedTime().asSeconds()  < (m_targetSwingTime / 2.0f))
		{
			m_swordRect->setRotation(360.0f -
				(m_swordClock.getElapsedTime().asSeconds() / (m_targetSwingTime * 0.5f)) * 90.0f
				);
		}
		else
		{
			m_swordRect->setRotation(
				270.0f + ((m_swordClock.getElapsedTime().asSeconds() - (m_targetSwingTime * 0.5f)) / (m_targetSwingTime * 0.5f)) * 90.0f
				);
		}

		if(m_swordClock.getElapsedTime().asSeconds() >= m_targetSwingTime)
		{
			m_swordRect->setRotation(0.0f);
			m_swordIsSwinging = false;
		}
	}

	if(m_meleeHitClock.getElapsedTime().asSeconds() >= m_meleeHitTime && m_hitted)
	{
		m_hitted  = false;
		m_animations->setCurrentAnimation("Hero_Walk_0");
	}
} 

void Player::setXSpeed(float xVel)
{
	m_xVel = xVel;
	m_markedForHalt = false;
}

void Player::haltXSpeed()
{
	m_markedForHalt = true;
}

void Player::takeDamage(float damage)
{
	if(m_meleeHitClock.getElapsedTime().asSeconds() > m_meleeHitTime)
	{
		m_meleeHitClock.restart();
		m_health -= damage;
		m_animations->setCurrentAnimation("Hero_Hit_0");

		m_hitted = true;

		//Check if character is dead
		if(m_health <= 0.0f)
		{m_isDead = true;}
	}
}