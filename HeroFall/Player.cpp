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
	m_animations->addAnimation("Avatar_Hit_0", 0.225f, this->m_xPos, this->m_yPos);
	m_animations->addAnimation("Avatar_Run_0", 0.5f, this->m_xPos, this->m_yPos);
	m_animations->addAnimation("Avatar_Attack_0", SettingsManager::getSettings()->PLAYER_SWORD_SWING_TIME, this->m_xPos, this->m_yPos);
	m_animations->addAnimation("Avatar_Attack_1", SettingsManager::getSettings()->PLAYER_SWORD_SWING_TIME, this->m_xPos, this->m_yPos);
	m_animations->addAnimation("Avatar_Idle_0", 0.5f, this->m_xPos, this->m_yPos);
	m_animations->addAnimation("Avatar_Jump_0", 0.5f, this->m_xPos, this->m_yPos);
	m_animations->addAnimation("Avatar_Jump_1", 0.5f, this->m_xPos, this->m_yPos);
	m_animations->addAnimation("Avatar_Jump_2", 0.5f, this->m_xPos, this->m_yPos);
	m_animations->setCurrentAnimation("Avatar_Idle_0");

	m_hitted = false;
	m_isOnGround = false;
	m_groundMarked = false;
	m_isIdle = false;

	m_hitBox = new sf::RectangleShape(sf::Vector2f(115.0f, 170.0f));
	m_hitBox->setFillColor(sf::Color(236, 116, 4, 128));
	m_hitBox->setPosition(m_animations->getCurrentSprite()->getGlobalBounds().left + 120,
		m_animations->getCurrentSprite()->getGlobalBounds().top + 75.0f);

	sf::RectangleShape* tempBox = new sf::RectangleShape(sf::Vector2f(115.0f, 50.0f));
	tempBox->setFillColor(sf::Color(255, 0, 0, 128));
	m_swordBoxes.push_back(tempBox);

	tempBox = new sf::RectangleShape(sf::Vector2f(109.0f, 58.0f));
	tempBox->setFillColor(sf::Color(64, 128, 255, 128));
	m_swordBoxes.push_back(tempBox);
}

Player::~Player()
{
	delete m_animations;
	delete m_hitBox;

	for(unsigned int a = 0; a < m_swordBoxes.size(); a++)
	{delete m_swordBoxes[a];}
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(*m_animations->getCurrentSprite());
	window->draw(*m_hitBox);

	if(m_swordIsSwinging)
	{
		window->draw(*m_swordBoxes[1]);
	}
}

void Player::move(float delta, std::vector<LevelObject*> levelObjects)
{
	m_groundMarked = false;

	m_yVel += getGravityDistance(delta);
	float m_yMove = delta * m_yVel;

	m_yPos += m_yMove;

	updateBoxes();

	for(unsigned int a = 0; a < levelObjects.size(); a++)
	{
		if(collidesWith(levelObjects[a]))
		{
			m_yPos -= m_yMove;

			if(m_yMove > 0.0f)
			{
				m_isOnGround = true;
				m_groundMarked = true;
			}
			
			updateBoxes();

			m_yVel = 0.0f;
			break;
		}
	}

	if(!m_groundMarked){m_isOnGround = false;}

	if(m_markedForHalt)
	{
		if(m_xVel > 0.0f)
		{
			m_xVel -= SettingsManager::getSettings()->PLAYER_SPEED_SIDE_HALTING * delta;
			if(m_xVel < 0.0f){m_xVel = 0.0f;}

			float m_xMove = delta * m_xVel;
			m_xPos += m_xMove;

			updateBoxes();

			for(unsigned int a = 0; a < levelObjects.size(); a++)
			{
				if(collidesWith(levelObjects[a]))
				{
					m_xPos -= m_xMove;
					m_xVel = 0.0f;

					updateBoxes();

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

			updateBoxes();

			for(unsigned int a = 0; a < levelObjects.size(); a++)
			{
				if(collidesWith(levelObjects[a]))
				{
					m_xPos -= m_xMove;
					m_xVel = 0.0f;

					updateBoxes();

					break;
				}
			}
		}
	}
	else
	{
		float m_xMove = delta * m_xVel;
		m_xPos += m_xMove;

		updateBoxes();

		for(unsigned int a = 0; a < levelObjects.size(); a++)
		{
			if(collidesWith(levelObjects[a]))
			{
				m_xPos -= m_xMove;
				m_xVel = 0.0f;

				updateBoxes();
		
				break;
			}
		}
	}

	updateBoxes();
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

		return(!(otherXPos > m_hitBox->getGlobalBounds().left + m_hitBox->getGlobalBounds().width
			|| otherXPos + otherSize.x < m_hitBox->getGlobalBounds().left
			|| otherYPos > m_hitBox->getGlobalBounds().top + m_hitBox->getGlobalBounds().height
			|| otherYPos + otherSize.y < m_hitBox->getGlobalBounds().top));
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
			if(m_swordIsSwinging && !m_swordHasHittedEnemy)
			{
				if(m_swordBoxes[1]->getGlobalBounds().intersects(tEnemy->getRect()->getGlobalBounds()))
				{
					enemies->at(a)->takeDamage(SettingsManager::getSettings()->DAMAGE_PLAYER_TO_ENEMY_PLACEHOLDER);
					m_swordHasHittedEnemy = true;
				}
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
			if(m_swordIsSwinging && !m_swordHasHittedEnemy && m_animations->isCurrentAnimation("Avatar_Attack_1"))
			{
				if(m_swordBoxes[1]->getGlobalBounds().intersects(tEnemy->getHitBox()))
				{
					enemies->at(a)->takeDamage(SettingsManager::getSettings()->DAMAGE_PLAYER_TO_ENEMY_TROLL);
					m_swordHasHittedEnemy = true;
				}
			}

			if(m_hitBox->getGlobalBounds().intersects(tEnemy->getHitBox()))
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
	m_animations->setCurrentAnimation("Avatar_Attack_1");
	AudioMixer::getInstance()->playSound("Sword_swings", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 10.0f, 0.0f, 1.0f);
}

void Player::update(float delta)
{
	AudioMixer::getInstance()->setListenerPosition(m_xPos, m_yPos);
	AudioMixer::getInstance()->setListenerDirection(m_xPos + 1.0f, m_yPos);

	if(InputManager::getInstance()->isKeyDown("P1_ATTACK_1") && !m_swordIsSwinging)
	{
		swingSword();
	}
	////////////////////////////////////////////////////
	/*
	Idle animationssaken fungerar inte perfekt här
	*/

	if(m_xVel == 0.0f && m_yVel == 0.0f 
		&& !m_hitted && !m_swordIsSwinging && !m_isIdle
		//&& m_prevIdlePos == m_animations->getCurrentSprite()->getPosition()
		)
	{
		m_animations->setCurrentAnimation("Avatar_Idle_0");
		m_isIdle = true;
		//std::cout << "Test\n";
	}
	else if(m_isIdle && (m_xVel != 0.0f || m_yVel != 0.0f))
	{
		m_animations->setCurrentAnimation("Avatar_Run_0");
		m_isIdle = false;
	}

	/////////////////////////////////////////////////
	if(m_swordIsSwinging)
	{
		if(m_swordClock.getElapsedTime().asSeconds() >= m_targetSwingTime)
		{
			m_swordIsSwinging = false;
			m_animations->setCurrentAnimation("Avatar_Run_0");
		}
	}

	if(m_meleeHitClock.getElapsedTime().asSeconds() >= m_meleeHitTime && m_hitted)
	{
		m_hitted  = false;
		m_animations->setCurrentAnimation("Avatar_Run_0");
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
		m_animations->setCurrentAnimation("Avatar_Hit_0");
		AudioMixer::getInstance()->playSound("Hurt_2", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 10.0f, 0.0f, 1.0f);

		m_hitted = true;

		//Check if character is dead
		if(m_health <= 0.0f)
		{m_isDead = true;}
	}
}

void Player::updateBoxes()
{
	m_animations->update(m_xPos, m_yPos);
	m_hitBox->setPosition(m_animations->getCurrentSprite()->getGlobalBounds().left + 120.0f,
		m_animations->getCurrentSprite()->getGlobalBounds().top + 75.0f);

	m_swordBoxes[0]->setPosition(m_animations->getCurrentSprite()->getGlobalBounds().left + 200.0f,
		m_animations->getCurrentSprite()->getGlobalBounds().top + 160.0f);

	m_swordBoxes[1]->setPosition(m_animations->getCurrentSprite()->getGlobalBounds().left + 210.0f,
		m_animations->getCurrentSprite()->getGlobalBounds().top + 170.0f);
}