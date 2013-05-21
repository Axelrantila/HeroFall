#include "AnimationManager.h"
#include "EnemyShooter.h"
#include "Player.h"
#include "ScoreManager.h"
#include "SettingsManager.h"
#include "Util.h"

#include <iostream>

const float PI = 3.14159265f;

EnemyShooter::EnemyShooter(float xPos, float yPos, float health, Player* player, sf::View* view)
	:Enemy(ENEMY_SHOOTER, xPos, yPos, health, view)
{
	m_shootTime = SettingsManager::getSettings()->ENEMY_SHOOTER_SHOOT_TIME;

	m_animations = new AnimationManager(this);
	m_animations->addAnimation("Shooter_Shoot_0", m_shootTime, this->getXPos(), this->getYPos());
	m_animations->addAnimation("Shooter_Die_0", m_deathTime, this->getXPos(), this->getYPos());
	m_animations->setCurrentAnimation("Shooter_Shoot_0");

	m_xVel = 0.0f;
	m_yVel = 0.0f;

	m_seen = false;
	m_shootClock.restart();
	m_canShoot = true;
	m_player = player;
}


EnemyShooter::~EnemyShooter()
{
	delete m_animations;
}

void EnemyShooter::update(float delta)
{
	m_animations->update(m_xPos, m_yPos);

	if(m_isDying)
	{
		if(!m_animations->isCurrentAnimation("Shooter_Die_0"))
		{
			m_dyingClock.restart();
			m_animations->setCurrentAnimation("Shooter_Die_0");
			ScoreManager::getInstance()->addScore(KILL_SHOOTER);
		}

		if(m_dyingClock.getElapsedTime().asSeconds() > m_deathTime)
		{
			m_isDead = true;
		}
	}
	else
	{
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

		if(m_animations->getCurrentAnimation()->getCurrentFrame() != 20)
		{
			m_canShoot = true;
		}
	}
}

void EnemyShooter::draw(sf::RenderWindow* window)
{
	window->draw(*m_animations->getCurrentSprite());
}

bool EnemyShooter::collidesWith(LevelObject* levelObject)
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

bool EnemyShooter::canShoot()
{
	if(m_isDying)
	{return false;}

	/*if(m_shootClock.getElapsedTime().asSeconds() >= m_shootTime)
	{
		m_shootClock.restart();

		if(m_seen)
		{
			return true;
		}
	}*/

	if(m_animations->getCurrentAnimation()->getCurrentFrame() == 20
		&& m_seen && m_canShoot)
	{
		m_canShoot = false;
		return true;
	}

	return false;
}

sf::Vector2f EnemyShooter::getProjectileSpawnPoint()
{
	return sf::Vector2f(m_animations->getCurrentSprite()->getGlobalBounds().left - 20.0f,
		m_animations->getCurrentSprite()->getGlobalBounds().top + m_animations->getCurrentSprite()->getGlobalBounds().height/2.0f);
}

sf::FloatRect EnemyShooter::getGlobalBounds()
{
	return m_animations->getCurrentSprite()->getGlobalBounds();
}

sf::Vector2f EnemyShooter::getProjectileSpeed()
{
	float dY = 0.0f;
	float y1 = m_player->getCenter().y;
	float y2 = m_animations->getCurrentSprite()->getGlobalBounds().top + m_animations->getCurrentSprite()->getGlobalBounds().height/2.0f;
	dY = y1-y2;

	float dX = 0.0f;
	float x1 = m_player->getCenter().x;
	float x2 =  m_animations->getCurrentSprite()->getGlobalBounds().left - 20.0f;
	dX = x1-x2;

	float angle = atan(dY/dX);

	sf::Vector2f projectileSpeed;
	projectileSpeed.x = SettingsManager::getSettings()->ENEMY_SHOOTER_PROJETILE_SPEED * cos(angle);
	projectileSpeed.y = SettingsManager::getSettings()->ENEMY_SHOOTER_PROJETILE_SPEED * sin(angle);

	//Correct the angle
	if((projectileSpeed.x > 0.0f && dX < 0.0f)
		 || (projectileSpeed.x < 0.0f && dX > 0.0f))
	{
		projectileSpeed.x *= -1;
	}

	if((projectileSpeed.y > 0.0f && dY < 0.0f)
		 || (projectileSpeed.y < 0.0f && dY > 0.0f))
	{
		projectileSpeed.y *= -1;
	}

	return projectileSpeed;
		//Cos x
		//-sin y
}