#include "AnimationManager.h"
#include "EnemyProjectile.h"
#include "EnemyShooter.h"
#include "LevelManager.h"
#include "SettingsManager.h"

EnemyProjectile::EnemyProjectile(EnemyShooter* parent, LevelManager* levelManager = nullptr)
	:Enemy(ENEMY_PROJECTILE, parent->getProjectileSpawnPoint().x, parent->getProjectileSpawnPoint().y, 1)
{
	m_xVel = -SettingsManager::getSettings()->ENEMY_SHOOTER_PROJETILE_SPEED;
	m_yVel = 0.0f;

	m_animations = new AnimationManager(this);
	m_animations->addAnimation("Projectile_Move_0", 1.0f, m_xPos, m_yPos);
	m_animations->setCurrentAnimation("Projectile_Move_0");

	m_levelManager = levelManager;


	m_particleSpawnTime = SettingsManager::getSettings()->ENEMY_SHOOTER_PROJECTILE_PARTICLE_SPAWN_TIME;
	m_clock.restart();
}


EnemyProjectile::~EnemyProjectile()
{
	delete m_animations;
}

void EnemyProjectile::move(float delta, std::vector<LevelObject*> levelObjects)
{
	m_xPos += m_xVel * delta;

	for(unsigned int a = 0; a < levelObjects.size(); a++)
	{
		if(collidesWith(levelObjects[a]))
		{
			m_isDead = true;
		}
	}
}

void EnemyProjectile::update(float delta)
{
	m_animations->update(this->m_xPos, this->m_yPos);

	if(m_clock.getElapsedTime().asSeconds() > m_particleSpawnTime)
	{
		m_levelManager->addParticles(sf::Vector2f(m_animations->getCurrentSprite()->getGlobalBounds().left + m_animations->getCurrentSprite()->getGlobalBounds().width/2,
			m_animations->getCurrentSprite()->getGlobalBounds().top + m_animations->getCurrentSprite()->getGlobalBounds().height/2), 1, PARTICLE_COLOR_FIRE);
		m_clock.restart();
	}

	if(m_isDying)
	{
		m_isDead = true;
	}
}

void EnemyProjectile::draw(sf::RenderWindow* window)
{
	window->draw(*m_animations->getCurrentSprite());
}

bool EnemyProjectile::collidesWith(LevelObject* levelObject)
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

sf::FloatRect EnemyProjectile::getGlobalBounds()
{
	return m_animations->getCurrentSprite()->getGlobalBounds();
}