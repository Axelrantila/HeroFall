#include "EnemyProjectile.h"


EnemyProjectile::EnemyProjectile(EnemyShooter* parent)
	:Enemy(ENEMY_PROJECTILE, parent->getProjectileSpawnPoint().x, parent->getProjectileSpawnPoint().y, 1)
{
	m_xVel = -400.0f;
	m_yVel = 0.0f;

	m_animations = new AnimationManager(this);
	m_animations->addAnimation("Projectile_Move_0", 1.0f, m_xPos, m_yPos);
	m_animations->setCurrentAnimation("Projectile_Move_0");
}


EnemyProjectile::~EnemyProjectile()
{
	delete m_animations;
}

void EnemyProjectile::move(float delta, std::vector<LevelObject*> levelObjects)
{
	m_xPos += m_xVel * delta;
}

void EnemyProjectile::update(float delta)
{
	m_animations->update(this->m_xPos, this->m_yPos);
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