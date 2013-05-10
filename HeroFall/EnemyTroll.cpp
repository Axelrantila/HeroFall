#include "AudioMixer.h"
#include "EnemyTroll.h"
#include "LevelObjectRectangle.h"
#include "ScoreManager.h"
#include "SpriteSheetLoader.h"

#include <iostream>

EnemyTroll::EnemyTroll(float xPos, float yPos, sf::View* view)
	:Enemy(ENEMY_TROLL, xPos, yPos, SettingsManager::getSettings()->ENEMY_TROLL_HEALTH, view)
{
	m_yVel = 0.0f;
	m_xVel = -SettingsManager::getSettings()->ENEMY_TROLL_SPEED_SIDE;

	m_animations = new AnimationManager(this);
	m_animations->addAnimation("Troll_Walk_0", 1.0f, m_xPos, m_yPos);
	m_animations->addAnimation("Troll_Hit_0", 0.225f, m_xPos, m_yPos);
	m_animations->addAnimation("Troll_Die_0", m_deathTime, m_xPos, m_yPos);
	m_animations->setCurrentAnimation("Troll_Walk_0");

	m_hitted = false;
	m_meleeHitTime = SettingsManager::getSettings()->ENEMY_TROLL_HIT_TIME_LIMIT_MELEE;
	m_hitClock.restart();

	m_hitBoxTest =  new sf::RectangleShape(sf::Vector2f(SettingsManager::getSettings()->ENEMY_TROLL_HITBOX_SIZE_X, SettingsManager::getSettings()->ENEMY_TROLL_HITBOX_SIZE_Y));
	m_hitBoxTest->setFillColor(sf::Color(64, 224, 208, 128));
}


EnemyTroll::~EnemyTroll()
{
	delete m_animations;
	delete m_hitBoxTest;
}

void EnemyTroll::update(float delta)
{
	if(m_isDying)
	{
		std::cout << m_animations->getCurrentAnimation()->getCurrentFrame() << std::endl;
		if(!m_animations->isCurrentAnimation("Troll_Die_0"))
		{
			m_dyingClock.restart();
			m_animations->setCurrentAnimation("Troll_Die_0");
			ScoreManager::getInstance()->addScore(KILL_TROLL);
		}
		else if(m_dyingClock.getElapsedTime().asSeconds() > m_deathTime)
		{
			m_isDead = true;
		}
	}

	else
	{
		m_hitBoxTest->setPosition(m_animations->getCurrentSprite()->getGlobalBounds().left + SettingsManager::getSettings()->ENEMY_TROLL_HITBOX_LOCAL_POSITION_X,
			m_animations->getCurrentSprite()->getGlobalBounds().top + SettingsManager::getSettings()->ENEMY_TROLL_HITBOX_LOCAL_POSITION_Y);

		if(m_hitClock.getElapsedTime().asSeconds() >= m_meleeHitTime && m_hitted)
		{
			m_hitted  = false;
			m_animations->setCurrentAnimation("Troll_Walk_0");
		}

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
				{m_seen = true;}
			}
		}
	}

	m_animations->update(m_xPos, m_yPos);
}

void EnemyTroll::draw(sf::RenderWindow* window)
{
	window->draw(*m_animations->getCurrentSprite());
	//window->draw(*m_hitBoxTest);
}

sf::FloatRect EnemyTroll::getHitBox()
{
	return m_hitBoxTest->getGlobalBounds();
}

bool EnemyTroll::collidesWith(LevelObject* levelObject)
{
	if(levelObject->getLevelObjectType() == LO_RECTANGLE)
	{
		sf::Vector2f otherSize = ((LevelObjectRectangle*)levelObject)->getSize();
		float otherXPos = ((LevelObjectRectangle*)levelObject)->getXPos();
		float otherYPos = ((LevelObjectRectangle*)levelObject)->getYPos();

		return(!(otherXPos > getXPos() + m_animations->getCurrentSprite()->getGlobalBounds().width
			|| otherXPos + otherSize.x < getXPos()
			|| otherYPos > getYPos() + m_animations->getCurrentSprite()->getGlobalBounds().height
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

		AudioMixer::getInstance()->playSound("Attack_hit_2", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 10.0f, 0.0f, 1.0f);
		AudioMixer::getInstance()->playSound("Hurt_troll", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 10.0f, 0.0f, 1.0f);

		//Check if character is dead
		if(m_health <= 0.0f)
		{
			m_isDying = true;
			AudioMixer::getInstance()->playSound("Death_troll", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 10.0f, 0.0f, 1.0f);
		}
	}
}

void EnemyTroll::move(float delta, std::vector<LevelObject*> levelObjects)
{
	if(m_seen && !m_isDying)
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

		if(!m_hitted)
		{
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
	}
}