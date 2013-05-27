#include "AnimationManager.h"
#include "EnemyBase.h"
#include "LevelObjectRectangle.h"
#include "Player.h"
#include "SettingsManager.h"
#include "Util.h"

EnemyBase::EnemyBase(float xPos, float yPos, sf::View* view)
	:Enemy(ENEMY_BASE, xPos, yPos, SettingsManager::getSettings()->ENEMY_BASE_HEALTH, view)
{
	m_yVel = 0.0f;
	m_xVel = -SettingsManager::getSettings()->ENEMY_BASE_SPEED_BASE 
		* Util::getInstance()->getRandomFloat(SettingsManager::getSettings()->ENEMY_BASE_SPEED_MIN_MULTIPLIER, SettingsManager::getSettings()->ENEMY_BASE_SPEED_MAX_MULTIPLIER);

	m_animations = new AnimationManager(this);
	m_animations->addAnimation("Base_Walk_0", 1.0f, xPos, yPos);
	m_animations->setCurrentAnimation("Base_Walk_0");

	m_seen = false;
	m_isDying = false;
	m_isDead = false;
	m_deathTime = 1.0f;
	m_timeDead = 0.0f;

	m_currentState = BASE_AI_WALKING_FORWARD;
	m_AIChangeLimit = 5.0f;
	m_AIStateClock.restart();
}


EnemyBase::~EnemyBase()
{
	delete m_animations;
}

void EnemyBase::update(float delta)
{
	m_animations->update(m_xPos, m_yPos);
	
	if(m_isDying)
	{
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
	return m_animations->getCurrentSprite()->getGlobalBounds();
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

		if((player->getCenter().x > this->getCenter().x && m_xVel < 0)
			|| (player->getCenter().x < this->getCenter().x && m_xVel > 0))
		{
			m_xVel *= -1;
		}
	}
}