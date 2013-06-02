#include "AnimationManager.h"
#include "EnemyBase.h"
#include "LevelObjectRectangle.h"
#include "Player.h"
#include "SettingsManager.h"
#include "Util.h"
#include "AudioMixer.h"

EnemyBase::EnemyBase(float xPos, float yPos, sf::View* view)
	:Enemy(ENEMY_BASE, xPos, yPos, SettingsManager::getSettings()->ENEMY_BASE_HEALTH, view)
{
	m_normalDirection = DIR_LEFT;
	m_direction = DIR_LEFT;

	m_yVel = 0.0f;
	m_xVel = -SettingsManager::getSettings()->ENEMY_BASE_SPEED_BASE 
		* Util::getInstance()->getRandomFloat(SettingsManager::getSettings()->ENEMY_BASE_SPEED_MIN_MULTIPLIER, SettingsManager::getSettings()->ENEMY_BASE_SPEED_MAX_MULTIPLIER);

	m_animations = new AnimationManager(this);
	m_animations->addAnimation("BaseWalking_Walking_0", 1.0f, xPos, yPos);
	m_animations->addAnimation("BaseDying_Dying_0", m_deathTime, xPos, yPos);
	m_animations->setCurrentAnimation("BaseWalking_Walking_0");

	m_seen = false;
	m_isDying = false;
	m_isDead = false;
	m_deathTime = 1.0f;
	m_timeDead = 0.0f;

	m_currentState = BASE_AI_WALKING_FORWARD;
	m_AIChangeLimit = 5.0f;
	m_AIStateClock.restart();

	m_hitBox.left = 110.0f;
	m_hitBox.top = 20.0f;
	m_hitBox.width = 95.0f;
	m_hitBox.height = 150.0f;

	d_attackBoxTest.setSize(sf::Vector2f(m_hitBox.width, m_hitBox.height));
	d_attackBoxTest.setFillColor(sf::Color(0,0,255,128));
}


EnemyBase::~EnemyBase()
{
	delete m_animations;
}

void EnemyBase::update(float delta)
{
	m_animations->update(m_xPos, m_yPos);
	
	m_hitBox.left = m_animations->getCurrentSprite()->getGlobalBounds().left + 110.0f;
	m_hitBox.top = m_animations->getCurrentSprite()->getGlobalBounds().top + 20.0f;

	d_attackBoxTest.setPosition(m_hitBox.left, m_hitBox.top);

	if(m_isDying)
	{
		AudioMixer::getInstance()->playSound("Death_Goblin", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 10.0f, 0.0f, 1.0f);
		m_animations->setCurrentAnimation("BaseDying_Dying_0", m_direction);
		m_timeDead += delta;
		if(m_timeDead > m_deathTime)
		{
			m_isDead = true;
		}
	}
	else
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
	}
}

void EnemyBase::draw(sf::RenderWindow* window)
{
	window->draw(*m_animations->getCurrentSprite());
	//window->draw(d_attackBoxTest);
}

bool EnemyBase::collidesWith(LevelObject* levelObject)
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

void EnemyBase::move(float delta, std::vector<LevelObject*> levelObjects)
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

void EnemyBase::takeDamage(float damage)
{
	m_isDying = true;
}

sf::FloatRect EnemyBase::getHitBox()
{
	return m_hitBox;
}

sf::Vector2f EnemyBase::getCenter()
{
	return sf::Vector2f(m_animations->getCurrentSprite()->getGlobalBounds().left + m_animations->getCurrentSprite()->getGlobalBounds().width/2.0f,
		m_animations->getCurrentSprite()->getGlobalBounds().top + m_animations->getCurrentSprite()->getGlobalBounds().height/2.0f);
}

void EnemyBase::updateState(Player* player)
{
	if(m_AIStateClock.getElapsedTime().asSeconds() > m_AIChangeLimit)
	{
		m_AIStateClock.restart();

		if(player->getCenter().x > this->getCenter().x && m_xVel < 0)
		{
			m_xVel *= -1;
			m_direction = DIR_RIGHT;
		}

		else if (player->getCenter().x < this->getCenter().x && m_xVel > 0)
		{
			m_xVel *= -1;
			m_direction = DIR_LEFT;
		}

		m_animations->setCurrentAnimation("BaseWalking_Walking_0", m_direction);
	}
}