#include "AudioMixer.h"
#include "EnemyTroll.h"
#include "LevelObjectRectangle.h"
#include "Player.h"
#include "ScoreManager.h"
#include "SpriteSheetLoader.h"
#include "Util.h"

#include <iostream>

EnemyTroll::EnemyTroll(float xPos, float yPos, sf::View* view)
	:Enemy(ENEMY_TROLL, xPos, yPos, SettingsManager::getSettings()->ENEMY_TROLL_HEALTH, view)
{
	m_normalDirection = DIR_LEFT;
	m_direction = DIR_LEFT;

	m_yVel = 0.0f;
	m_xVel = -SettingsManager::getSettings()->ENEMY_TROLL_SPEED_SIDE;

	m_attackStage1Time = SettingsManager::getSettings()->ENEMY_TROLL_ATTACK_STAGE_1_TIME;
	m_attackStage2Time = SettingsManager::getSettings()->ENEMY_TROLL_ATTACK_STAGE_2_TIME;

	//Ugly hack to fix some frameratedrop issues
	SpriteSheetLoader::getInstance()->getSheet("TrollLWalk");
	SpriteSheetLoader::getInstance()->getSheet("TrollLDie");
	SpriteSheetLoader::getInstance()->getSheet("TrollLHit");
	SpriteSheetLoader::getInstance()->getSheet("TrollLAttack");

	m_animations = new AnimationManager(this);
	m_animations->addAnimation("TrollLWalk_Walk_0", 1.0f, m_xPos, m_yPos);
	m_animations->addAnimation("TrollLHit_Hit_0", 1.0f, m_xPos, m_yPos);
	m_animations->addAnimation("TrollLDie_Die_0", m_deathTime, m_xPos, m_yPos);
	m_animations->addAnimation("TrollLAttack_Attack_0", m_attackStage1Time, m_xPos, m_yPos);
	m_animations->setCurrentAnimation("TrollLWalk_Walk_0");

	m_hitted = false;
	m_meleeHitTime = SettingsManager::getSettings()->ENEMY_TROLL_HIT_TIME_LIMIT_MELEE;
	
	m_hitBox =  new sf::RectangleShape(sf::Vector2f(SettingsManager::getSettings()->ENEMY_TROLL_HITBOX_SIZE_X, SettingsManager::getSettings()->ENEMY_TROLL_HITBOX_SIZE_Y));
	m_hitBox->setFillColor(sf::Color(64, 224, 208, 128));

	m_currentAIState = TROLL_AI_WALKING_FORWARD;
	m_AIChangeLimit = SettingsManager::getSettings()->ENEMY_TROLL_AI_CHANGE_LIMIT_TIME;

	m_isATroll = true;

	m_hitClock.restart();
	m_AIStateClock.restart();
	m_attackClock.restart();

	d_attackBox.setFillColor(sf::Color::Cyan);
}


EnemyTroll::~EnemyTroll()
{
	delete m_animations;
	delete m_hitBox;
}

void EnemyTroll::update(float delta)
{
	m_animations->update(m_xPos, m_yPos);

	updateHitBox();

	if(m_isDying)
	{
		if(m_dyingClock.getElapsedTime().asSeconds() > m_deathTime)
		{
			m_isDead = true;
		}
	}

#pragma region FORWARD/BACKWARD
	else if(m_currentAIState == TROLL_AI_WALKING_FORWARD || m_currentAIState == TROLL_AI_WALKING_BACKWARD)
	{	
		//Check if the enemy has been seen
		if(m_view != nullptr)
		{
			if(!m_seen)
			{
				sf::FloatRect viewField(
				m_view->getCenter().x - m_view->getSize().x / 2.0f
				,m_view->getCenter().y - m_view->getSize().y / 2.0f
				,m_view->getSize().x
				,m_view->getSize().y);

				if(m_animations->getCurrentSprite()->getGlobalBounds().intersects(viewField))
				{
					m_seen = true;
				}
			}
		}

		if(!m_hitted)
		{
			m_animations->setCurrentAnimation("TrollLWalk_Walk_0", m_direction);
		}

		else if(m_hitClock.getElapsedTime().asSeconds() >= m_meleeHitTime && m_hitted)
		{
			m_hitted  = false;
			m_animations->setCurrentAnimation("TrollLWalk_Walk_0", m_direction);
		}
	}
#pragma endregion

#pragma region ATTACK
	else if(m_currentAIState == TROLL_AI_ATTACK_0)
	{
		m_animations->setCurrentAnimation("TrollLAttack_Attack_0", m_direction);
	}
#pragma endregion
}

void EnemyTroll::draw(sf::RenderWindow* window)
{
	window->draw(*m_animations->getCurrentSprite());
	window->draw(*m_hitBox);
	window->draw(d_attackBox);
}

sf::FloatRect EnemyTroll::getHitBox()
{
	return m_hitBox->getGlobalBounds();
}

bool EnemyTroll::collidesWith(LevelObject* levelObject)
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

void EnemyTroll::takeDamage(float damage)
{
	if(m_hitClock.getElapsedTime().asSeconds() > m_meleeHitTime)
	{
		m_hitClock.restart();
		m_health -= damage;
		m_hitted = true;

		AudioMixer::getInstance()->playSound("Attack_hit_2", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 10.0f, 0.0f, 1.0f);
		AudioMixer::getInstance()->playSound("Hurt_troll", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 10.0f, 0.0f, 1.0f);

		//Check if character is dead
		if(m_health <= 0.0f)
		{
			m_isDying = true;
			AudioMixer::getInstance()->playSound("Death_troll", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 10.0f, 0.0f, 1.0f);
			m_dyingClock.restart();
			
			ScoreManager::getInstance()->addScore(KILL_TROLL);

			m_animations->setCurrentAnimation("TrollLDie_Die_0", m_direction);
		}

		else
		{
			m_animations->setCurrentAnimation("TrollLHit_Hit_0", m_direction);
		}
	}
}

void EnemyTroll::move(float delta, std::vector<LevelObject*> levelObjects)
{
#pragma region Forward/Backward
	if(m_currentAIState == TROLL_AI_WALKING_FORWARD || m_currentAIState == TROLL_AI_WALKING_BACKWARD)
	{
		if(m_seen && !m_isDying)
		{
			m_yVel += getGravityDistance(delta);
			float yMove = delta * m_yVel;
			m_yPos += yMove;
			updateHitBox();
			for(unsigned int a = 0; a < levelObjects.size(); a++)
			{
				if(collidesWith(levelObjects[a]))
				{
					m_yPos -= yMove;
					m_yVel = 0.0f;
					updateHitBox();
					break;
				}
			}

			

			if(!m_hitted)
			{
				float xMove = delta * m_xVel;
				m_xPos += xMove;
				updateHitBox();
				for(unsigned int a = 0; a < levelObjects.size(); a++)
				{
					if(collidesWith(levelObjects[a]))
					{
						m_xPos -= xMove;
						m_xVel = 0.0f;
						updateHitBox();
						break;
					}
				}
			}
		}
	}
#pragma endregion
}

sf::Vector2f EnemyTroll::getCenter()
{
	return sf::Vector2f(m_animations->getCurrentSprite()->getGlobalBounds().left + m_animations->getCurrentSprite()->getGlobalBounds().width/2.0f,
		m_animations->getCurrentSprite()->getGlobalBounds().top + m_animations->getCurrentSprite()->getGlobalBounds().height/2.0f);
}

void EnemyTroll::updateState(Player* player)
{
	//Attack stage 0
	if(m_currentAIState == TROLL_AI_ATTACK_0)
	{
		if(m_attackClock.getElapsedTime().asSeconds() > m_attackStage1Time)
		{
			m_currentAIState = TROLL_AI_WALKING_FORWARD;
			m_attackClock.restart();
		}
	}
	//Attack stage 1
	else if(m_currentAIState == TROLL_AI_ATTACK_1
		&& m_attackClock.getElapsedTime().asSeconds() > m_attackStage2Time)
	{
		m_currentAIState = TROLL_AI_WALKING_FORWARD;
		m_AIStateClock.restart(); 
	}

	//Look at what the next state should be
	else if(m_AIStateClock.getElapsedTime().asSeconds() > m_AIChangeLimit)
	{
		TrollAIState newAIState = TROLL_AI_WALKING_FORWARD;
		float distance = Util::getInstance()->distance(player->getCenter(), this->getCenter());

		if(abs(distance) < SettingsManager::getSettings()->ENEMY_TROLL_AI_WALKING_BACKWARDS_DISTANCE_LIMIT
			&& !m_hitted
			&&
				((player->getXPos() < m_hitBox->getGlobalBounds().left && m_direction == DIR_LEFT)
				|| (player->getXPos() > m_hitBox->getGlobalBounds().left && m_direction == DIR_RIGHT)))
		{
			newAIState = TROLL_AI_ATTACK_0;
			m_attackClock.restart();
		}

		//////////////////////////////////////////////////////////////////////
		else if(player->getXPos() < m_hitBox->getGlobalBounds().left
			&& m_direction == DIR_RIGHT)
		{
			m_direction = DIR_LEFT;
			m_xVel *= -1.0f;
		}
		else if(player->getXPos() > m_hitBox->getGlobalBounds().left
			&&m_direction == DIR_LEFT)
		{
			m_direction = DIR_RIGHT;
			m_xVel *= -1.0f;
		}

		m_currentAIState = newAIState;
		m_AIStateClock.restart();
	}
}

sf::FloatRect EnemyTroll::getAttackHitbox()
{
	if(!m_animations->isCurrentAnimation("TrollLAttack_Attack_0")
		|| (m_animations->isCurrentAnimation("TrollLAttack_Attack_0") && m_animations->getCurrentAnimation()->getCurrentFrame() < 9 && m_animations->getCurrentAnimation()->getCurrentFrame() > 37))
	{
		return sf::FloatRect(-10000.0f, -10000.0f, 1.0f, 1.0f);
	}

	else if(m_direction == DIR_LEFT)
	{
		sf::FloatRect rect(m_animations->getCurrentSprite()->getGlobalBounds().left + 10.0f,
			m_animations->getCurrentSprite()->getGlobalBounds().top + 275.0f,
			185.0f, 160.0f);
		
		d_attackBox.setPosition(rect.left, rect.top);
		d_attackBox.setSize(sf::Vector2f(rect.width, rect.height));

		return rect;
	}

	else
	{
		sf::FloatRect rect(m_animations->getCurrentSprite()->getGlobalBounds().left + 460.0f,
			m_animations->getCurrentSprite()->getGlobalBounds().top + 275.0f,
			185.0f, 160.0f);

		d_attackBox.setPosition(rect.left, rect.top);
		d_attackBox.setSize(sf::Vector2f(rect.width, rect.height));

		return rect;
	}
}

void EnemyTroll::updateHitBox()
{
	m_animations->update(m_xPos, m_yPos);

	if(m_direction == DIR_LEFT)
	{
		m_hitBox->setPosition(m_animations->getCurrentSprite()->getGlobalBounds().left + SettingsManager::getSettings()->ENEMY_TROLL_HITBOX_LOCAL_POSITION_X,
			m_animations->getCurrentSprite()->getGlobalBounds().top + SettingsManager::getSettings()->ENEMY_TROLL_HITBOX_LOCAL_POSITION_Y);
	}
	else if(m_direction == DIR_RIGHT)
	{
		m_hitBox->setPosition(m_animations->getCurrentSprite()->getGlobalBounds().left + SettingsManager::getSettings()->ENEMY_TROLL_HITBOX_LOCAL_POSITION_X * 0.5f,
			m_animations->getCurrentSprite()->getGlobalBounds().top + SettingsManager::getSettings()->ENEMY_TROLL_HITBOX_LOCAL_POSITION_Y);
	}
}