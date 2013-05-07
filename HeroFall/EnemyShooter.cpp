#include "AnimationManager.h"
#include "EnemyShooter.h"


EnemyShooter::EnemyShooter(float xPos, float yPos, float health)
	:Enemy(ENEMY_SHOOTER, xPos, yPos, health)
{
	m_shootTime = 6.0f;

	m_animations = new AnimationManager(this);
	m_animations->addAnimation("Shooter_Shoot_0", m_shootTime, this->getXPos(), this->getYPos());
	m_animations->setCurrentAnimation("Shooter_Shoot_0");

	m_xVel = 0.0f;
	m_yVel = 0.0f;

	m_shootClock.restart();
}


EnemyShooter::~EnemyShooter()
{
}

void EnemyShooter::update(float delta)
{
	m_animations->update(m_xPos, m_yPos);
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
	if(m_shootClock.getElapsedTime().asSeconds() >= m_shootTime)
	{
		m_shootClock.restart();
		return true;
	}

	return false;
}

sf::Vector2f EnemyShooter::getProjectileSpawnPoint()
{
	return sf::Vector2f(m_animations->getCurrentSprite()->getGlobalBounds().left - 50.0f,
		m_animations->getCurrentSprite()->getGlobalBounds().top + m_animations->getCurrentSprite()->getGlobalBounds().height/2.0f);
}

sf::FloatRect EnemyShooter::getGlobalBounds()
{
	return m_animations->getCurrentSprite()->getGlobalBounds();
}