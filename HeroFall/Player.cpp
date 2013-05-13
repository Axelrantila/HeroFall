#include "AudioMixer.h"
#include "EnemyBomb.h"
#include "EnemyGoblin.h"
#include "EnemyPlaceholder.h"
#include "EnemyProjectile.h"
#include "EnemyTroll.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "LevelObjectRectangle.h"
#include "Player.h"
#include "SpriteSheetLoader.h"
#include "Util.h"

#include <iostream>
#include <math.h>

Player::Player(float xPos, float yPos, LevelManager* levelManager)
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
	m_animations->addAnimation("Avatar_CAttack_0", SettingsManager::getSettings()->PLAYER_SWORD_SWING_TIME, this->m_xPos, this->m_yPos);
	m_animations->addAnimation("Avatar_Idle_0", 0.5f, this->m_xPos, this->m_yPos);
	m_animations->addAnimation("Avatar_Jump_0", Util::getInstance()->jumpUpTime(), this->m_xPos, this->m_yPos);
	m_animations->addAnimation("Avatar_Jump_1", 0.5f, this->m_xPos, this->m_yPos, true);
	m_animations->addAnimation("Avatar_Jump_2", 0.5f, this->m_xPos, this->m_yPos);
	m_animations->addAnimation("Avatar_Die_0", m_deathTime, this->m_xPos, this->m_yPos);
	m_animations->setCurrentAnimation("Avatar_Idle_0");

	m_hitted = false;
	m_isOnGround = false;
	m_groundMarked = false;
	m_isIdle = false;
	m_isBlocking = false;
	m_jumping = false;

	m_hitBox = new sf::RectangleShape(sf::Vector2f(115.0f, 170.0f));
	m_hitBox->setFillColor(sf::Color(236, 116, 4, 128));
	m_hitBox->setPosition(m_animations->getCurrentSprite()->getGlobalBounds().left + 120,
		m_animations->getCurrentSprite()->getGlobalBounds().top + 75.0f);

	m_swordBoxesMap.insert(std::pair<Animation*, sf::RectangleShape>(m_animations->getAnimation("Avatar_Attack_0"), sf::RectangleShape(sf::Vector2f(115.0f, 50.0f))));
	m_swordBoxesMap.insert(std::pair<Animation*, sf::RectangleShape>(m_animations->getAnimation("Avatar_Attack_1"), sf::RectangleShape(sf::Vector2f(109.0f, 58.0f))));
	m_swordBoxesMap.insert(std::pair<Animation*, sf::RectangleShape>(m_animations->getAnimation("Avatar_CAttack_0"), sf::RectangleShape(sf::Vector2f(115.0f, 50.0f))));

	m_currentAttack = 0;
	m_levelManager = levelManager;

	m_jumping = false;
	m_currentJumpStage = JUMPING_LANDING;

	m_delta = 0.0f;
}

Player::~Player()
{
	delete m_animations;
	delete m_hitBox;
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(*m_animations->getCurrentSprite());
	/*window->draw(*m_hitBox);*/
}

void Player::move(float delta, std::vector<LevelObject*> levelObjects)
{
	m_delta = delta;

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
				m_jumping = false;
			}
			
			updateBoxes();

			m_yVel = 0.0f;
			break;
		}
	}

	if(!m_groundMarked)
	{
		m_isOnGround = false;
	}

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

	if(m_yVel < 0.0f)
	{
		m_jumping = true;
		m_currentJumpStage = JUMPING_UPWARDS;
	}

	else if(m_yVel > 0.0f)
	{
		if(m_jumping && m_currentJumpStage != JUMPING_FALLING)
		{
			m_currentJumpStage = JUMPING_LANDING;
		}
	}
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
	for(unsigned int a = 0; a < enemies->size(); a++)
	{
		if(enemies->at(a)->isDying()){continue;}

#pragma region ENEMY PLACEHOLDER
		if(enemies->at(a)->getType() == ENEMY_PLACEHOLDER)
		{
			EnemyPlaceholder* tEnemy = ((EnemyPlaceholder*)enemies->at(a));
			if(m_swordIsSwinging && !m_swordHasHittedEnemy)
			{
				if(m_swordBoxesMap[m_animations->getCurrentAnimation()].getGlobalBounds().intersects(tEnemy->getRect()->getGlobalBounds()))
				{
					enemies->at(a)->takeDamage(SettingsManager::getSettings()->DAMAGE_PLAYER_TO_ENEMY_PLACEHOLDER);
					m_swordHasHittedEnemy = true;
					ComboManager::getInstance()->increaseComboMeter();
				}
			}

			if(m_animations->getCurrentSprite()->getGlobalBounds().intersects(tEnemy->getRect()->getGlobalBounds())
				&& !m_isBlocking)
			{
				this->takeDamage(SettingsManager::getSettings()->DAMAGE_ENEMY_PLACEHOLDER_TO_PLAYER);
			}
		}
#pragma endregion

#pragma region TROLL
		else if(enemies->at(a)->getType() == ENEMY_TROLL)
		{
			EnemyTroll* tEnemy = ((EnemyTroll*)enemies->at(a));
			if(m_swordIsSwinging && !m_swordHasHittedEnemy )
			{
				if(m_swordBoxesMap[m_animations->getCurrentAnimation()].getGlobalBounds().intersects(tEnemy->getHitBox()))
				{
					if(m_animations->getCurrentAnimation()->getName() == "Avatar_CAttack_0")
					{
						enemies->at(a)->takeDamage(SettingsManager::getSettings()->DAMAGE_PLAYER_TO_ENEMY_TROLL * 1.25f);
					}
					else
					{
						enemies->at(a)->takeDamage(SettingsManager::getSettings()->DAMAGE_PLAYER_TO_ENEMY_TROLL);
					}

					m_swordHasHittedEnemy = true;
					m_levelManager->addParticles(sf::Vector2f(m_swordBoxesMap[m_animations->getCurrentAnimation()].getGlobalBounds().left + m_swordBoxesMap[m_animations->getCurrentAnimation()].getGlobalBounds().width
						, m_swordBoxesMap[m_animations->getCurrentAnimation()].getGlobalBounds().top),
						100, PARTICLE_COLOR_BLOOD);
					ComboManager::getInstance()->increaseComboMeter();
				}
			}

			if(m_hitBox->getGlobalBounds().intersects(tEnemy->getHitBox()) && !m_isBlocking)
			{
				this->takeDamage(SettingsManager::getSettings()->DAMAGE_ENEMY_TROLL_TO_PLAYER);
			}
		}
#pragma endregion

#pragma region BOMB
		//Bomb
		else if(enemies->at(a)->getType() == ENEMY_BOMB)
		{
			if(((EnemyBomb*)enemies->at(a))->hasBlased()
				&& ((EnemyBomb*)enemies->at(a))->getGlobalBounds().intersects(m_hitBox->getGlobalBounds()))
			{
				takeDamageOverTime(50.0f, m_delta);
			}
		}
#pragma endregion

#pragma region GOBLIN
		//Goblin
		else if(enemies->at(a)->getType() == ENEMY_GOBLIN)
		{
			if(m_swordIsSwinging && !m_swordHasHittedEnemy)
			{
				if(((EnemyGoblin*)enemies->at(a))->getGlobalBounds().intersects
					(m_animations->getCurrentSprite()->getGlobalBounds()))
				{
					enemies->at(a)->takeDamage(1.0f);
					m_swordHasHittedEnemy = true;
					m_levelManager->addParticles(sf::Vector2f(m_swordBoxesMap[m_animations->getCurrentAnimation()].getGlobalBounds().left + m_swordBoxesMap[m_animations->getCurrentAnimation()].getGlobalBounds().width
						, m_swordBoxesMap[m_animations->getCurrentAnimation()].getGlobalBounds().top),
						100);
					ComboManager::getInstance()->increaseComboMeter();
				}
			}
		}
#pragma endregion

#pragma region PROJECTILE
		//Projectile
		else if (enemies->at(a)->getType() == ENEMY_PROJECTILE)
		{
			if(((EnemyProjectile*)enemies->at(a))->getGlobalBounds().intersects(m_hitBox->getGlobalBounds()))
			{
				if(m_isBlocking)
				{
					enemies->at(a)->takeDamage(1.0f);
				}
				else
				{
					this->takeDamage(SettingsManager::getSettings()->DAMAGE_ENEMY_PROJECTILE_TO_PLAYER);
				}
			}
		}
#pragma endregion

#pragma region SHOOTER
		//Shooter
		else if(enemies->at(a)->getType() == ENEMY_SHOOTER)
		{
			if(((EnemyProjectile*)enemies->at(a))->getGlobalBounds().intersects(m_swordBoxesMap[m_animations->getCurrentAnimation()].getGlobalBounds()))
			{
				enemies->at(a)->takeDamage(SettingsManager::getSettings()->DAMAGE_PLAYER_TO_ENEMY_SHOOTER);
				m_swordHasHittedEnemy = true;
				m_levelManager->addParticles(sf::Vector2f(m_swordBoxesMap[m_animations->getCurrentAnimation()].getGlobalBounds().left + m_swordBoxesMap[m_animations->getCurrentAnimation()].getGlobalBounds().width
					, m_swordBoxesMap[m_animations->getCurrentAnimation()].getGlobalBounds().top),
					100);
				ComboManager::getInstance()->increaseComboMeter();
			}
		}
#pragma endregion
	}
}

sf::Vector2f Player::getCenter()
{
	return sf::Vector2f(m_xPos + m_animations->getCurrentSprite()->getGlobalBounds().width/2.0f,
		m_yPos + m_animations->getCurrentSprite()->getGlobalBounds().height/2.0f);
}

void Player::swingSword(AttackType type)
{
	m_swordIsSwinging = true;
	m_swordHasHittedEnemy = false;
	m_swordClock.restart();
	AudioMixer::getInstance()->playSound("Sword_swings", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 10.0f, 0.0f, 1.0f);

	if(type == ATTACK_COMBO_0)
	{
		m_animations->setCurrentAnimation("Avatar_CAttack_0");
	}

	else if(type == ATTACK_NORMAL)
	{
		m_currentAttack = (unsigned int)(Util::getInstance()->getRandomFloat(0, 1.99999f));
		m_animations->setCurrentAnimation("Avatar_Attack_" + Util::getInstance()->toString(m_currentAttack));
	}
}

void Player::update(float delta)
{
	AudioMixer::getInstance()->setListenerPosition(m_xPos, m_yPos);
	AudioMixer::getInstance()->setListenerDirection(m_xPos + 1.0f, m_yPos);

	//Check if character is dead
	if(m_health <= 0.0f && !m_isDying)
	{
		m_isDying = true;
		m_animations->setCurrentAnimation("Avatar_Die_0");
		m_dyingClock.restart();
	}
	
	if(m_isDying)
	{
		if(m_dyingClock.getElapsedTime().asSeconds() > m_deathTime)
		{
			m_isDead = true;
		}
	}
	else
	{
		if(m_isBlocking){}

		//Jump
		if(m_jumping
			&& !m_swordIsSwinging
			&& !m_hitted)
		{
			if(m_yVel < 0.0f)
			{
				m_currentJumpStage = JUMPING_UPWARDS;
			}
			else
			{
				m_currentJumpStage = JUMPING_FALLING;
			}

			////////////////////////////////////////////////////////////////
			if(m_currentJumpStage == JUMPING_UPWARDS
				&& !m_animations->isCurrentAnimation("Avatar_Jump_0"))
			{
				m_animations->setCurrentAnimation("Avatar_Jump_0");
			}

			else if(m_currentJumpStage == JUMPING_FALLING
				&& !m_animations->isCurrentAnimation("Avatar_Jump_1"))
			{
				m_animations->setCurrentAnimation("Avatar_Jump_1");
			}

			else if(m_currentJumpStage == JUMPING_LANDING
				&& !m_animations->isCurrentAnimation("Avatar_Jump_2"))
			{
				m_animations->setCurrentAnimation("Avatar_Jump_2");
			}
		}

		//Attack
		if(!m_swordIsSwinging)
		{
			if(InputManager::getInstance()->d_testCombo())
			{
				swingSword(ATTACK_COMBO_0);
			}
	
			else if(InputManager::getInstance()->isKeyDown("P1_ATTACK_1"))
			{
				swingSword();
			}
		}

		//Idle
		if(m_xVel == 0.0f && m_yVel == 0.0f 
			&& !m_hitted && !m_swordIsSwinging && !m_isIdle
			)
		{
			m_animations->setCurrentAnimation("Avatar_Idle_0");
			m_isIdle = true;
		}

		//Run
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

				if(m_isOnGround)
				{
					m_animations->setCurrentAnimation("Avatar_Idle_0");
				}
				else
				{
					m_animations->setCurrentAnimation("Avatar_Jump_1");
				}
			}
		}

		if(m_meleeHitClock.getElapsedTime().asSeconds() >= m_meleeHitTime
			&& m_hitted
			&& m_animations->getCurrentAnimation() != m_animations->getAnimation("Avatar_Idle_0"))
		{
			m_hitted  = false;
			if(m_isOnGround)
			{
				m_animations->setCurrentAnimation("Avatar_Idle_0");
			}
	
		}
	}
} 

void Player::setXSpeed(float xVel)
{
	m_xVel = xVel;
	m_markedForHalt = false;
	
	if(m_animations->getCurrentAnimation() != m_animations->getAnimation("Avatar_Run_0")
		&& !m_swordIsSwinging
		&& m_isOnGround)
	{
		m_animations->setCurrentAnimation("Avatar_Run_0");
	}
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
		AudioMixer::getInstance()->playSound("Hurt_player", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 10.0f, 0.0f, 1.0f);

		m_hitted = true;
	}
}

void Player::updateBoxes()
{
	m_animations->update(m_xPos, m_yPos);
	m_hitBox->setPosition(m_animations->getCurrentSprite()->getGlobalBounds().left + 120.0f,
		m_animations->getCurrentSprite()->getGlobalBounds().top + 75.0f);

	for(std::map<Animation*, sf::RectangleShape>::iterator it = m_swordBoxesMap.begin();
		it != m_swordBoxesMap.end(); ++it)
	{
		if(it->first == m_animations->getAnimation("Avatar_Attack_0")
			|| it->first == m_animations->getAnimation("Avatar_CAttack_0"))
		{
			it->second.setPosition(m_animations->getCurrentSprite()->getGlobalBounds().left + 200.0f,
		m_animations->getCurrentSprite()->getGlobalBounds().top + 160.0f);
		}

		else if(it->first == m_animations->getAnimation("Avatar_Attack_1"))
		{
			it->second.setPosition(m_animations->getCurrentSprite()->getGlobalBounds().left + 210.0f,
		m_animations->getCurrentSprite()->getGlobalBounds().top + 170.0f);
		}
	}
}

void Player::block(bool blocking)
{
	m_isBlocking = blocking;
}

void Player::takeDamageOverTime(float damage, float delta)
{
	m_health -= (damage * delta);
}