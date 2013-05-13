#include "EnemyBomb.h"
#include "EnemyGoblin.h"
#include "LevelObjectRectangle.h"
#include "SpriteSheetLoader.h"
#include "AudioMixer.h"

EnemyBomb::EnemyBomb(EnemyGoblin* parent)
	:Enemy(ENEMY_BOMB, parent->getBombSpawnPoint().x, parent->getBombSpawnPoint().y, 1.0f)
{
	d_sprite = SpriteSheetLoader::getInstance()->getSprite("Bomb", "Bomb_Placeholder");
	d_sprite->setPosition(parent->getBombSpawnPoint());

	m_yVel = 0.0f;
	m_xVel = 0.0f;

	m_bombBlastArea.setSize(sf::Vector2f(400.0f, 400.0f));
	m_bombBlastArea.setFillColor(sf::Color::Yellow);

	m_bombHasBlasted = false;
	m_bombBlastCurrentTime = 0.0f;
	m_bombBlastTotalTime = SettingsManager::getSettings()->ENEMY_GOBLIN_BOMB_AOE_DURATION;
}


EnemyBomb::~EnemyBomb()
{
}

void EnemyBomb::move(float delta, std::vector<LevelObject*> levelObjects)
{
	if(m_bombHasBlasted)
	{
		m_bombBlastCurrentTime += delta;

		if(m_bombBlastCurrentTime >= m_bombBlastTotalTime)
		{
			m_isDead = true;
		}
	}

	else
	{
		m_yVel += getGravityDistance(delta);
		m_yPos += m_yVel * delta;
		d_sprite->setPosition(m_xPos, m_yPos);

		for(unsigned int a = 0; a < levelObjects.size(); a++)
		{
			if(collidesWith(levelObjects[a]))
			{
				//Spela up ljud här
				AudioMixer::getInstance()->removeSound(this);
				AudioMixer::getInstance()->playSound("Explosion_1", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 1200.0f, 10.0f, 1.0f);
				m_bombHasBlasted = true;

				m_bombBlastArea.setPosition(d_sprite->getGlobalBounds().left + d_sprite->getGlobalBounds().width / 2.0f - m_bombBlastArea.getSize().x / 2.0f
					,d_sprite->getGlobalBounds().top + d_sprite->getGlobalBounds().height - m_bombBlastArea.getSize().y);

				break;
			}
		}
	}
}

void EnemyBomb::draw(sf::RenderWindow* window)
{
	if(m_bombHasBlasted)
	{
		window->draw(m_bombBlastArea);
	}
	else
	{
		window->draw(*d_sprite);
	}
}

sf::FloatRect EnemyBomb::getGlobalBounds()
{
	if(m_bombHasBlasted)
	{
		return m_bombBlastArea.getGlobalBounds();
	}
	else
	{
		return d_sprite->getGlobalBounds();
	}
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