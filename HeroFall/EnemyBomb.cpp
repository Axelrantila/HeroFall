#include "EnemyBomb.h"
#include "EnemyGoblin.h"
#include "LevelObjectRectangle.h"
#include "SpriteSheetLoader.h"

EnemyBomb::EnemyBomb(EnemyGoblin* parent)
	:Enemy(ENEMY_BOMB, parent->getBombSpawnPoint().x, parent->getBombSpawnPoint().y, 1.0f)
{
	d_sprite = SpriteSheetLoader::getInstance()->getSprite("Bomb", "Bomb_Placeholder");
	d_sprite->setPosition(parent->getBombSpawnPoint());

	m_yVel = 0.0f;
	m_xVel = 0.0f;
}


EnemyBomb::~EnemyBomb()
{
}

void EnemyBomb::move(float delta, std::vector<LevelObject*> levelObjects)
{
	m_yVel += getGravityDistance(delta);
	m_yPos += m_yVel * delta;
	d_sprite->setPosition(m_xPos, m_yPos);

	for(unsigned int a = 0; a < levelObjects.size(); a++)
	{
		if(collidesWith(levelObjects[a]))
		{
			//Spela up ljud här

			m_isDead = true;
			break;
		}
	}
}

void EnemyBomb::draw(sf::RenderWindow* window)
{
	window->draw(*d_sprite);
}

sf::FloatRect EnemyBomb::getGlobalBounds()
{
	return d_sprite->getGlobalBounds();
}

bool EnemyBomb::collidesWith(LevelObject* levelObject)
{
	if(levelObject->getLevelObjectType() == LO_RECTANGLE)
	{
		sf::Vector2f otherSize = ((LevelObjectRectangle*)levelObject)->getSize();
		float otherXPos = ((LevelObjectRectangle*)levelObject)->getXPos();
		float otherYPos = ((LevelObjectRectangle*)levelObject)->getYPos();

		return(!(otherXPos > getXPos() + d_sprite->getGlobalBounds().width
			|| otherXPos + otherSize.x < getXPos()
			|| otherYPos > getYPos() + d_sprite->getGlobalBounds().height
			|| otherYPos + otherSize.y < getYPos()));
	}

	return false;
}