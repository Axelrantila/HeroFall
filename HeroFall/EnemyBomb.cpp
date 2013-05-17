#include "EnemyBomb.h"
#include "EnemyGoblin.h"
#include "LevelObjectRectangle.h"
#include "SpriteSheetLoader.h"
#include "AudioMixer.h"

EnemyBomb::EnemyBomb(EnemyGoblin* parent)
	:Enemy(ENEMY_BOMB, parent->getBombSpawnPoint().x, parent->getBombSpawnPoint().y, 1.0f)
{
	m_sprite = SpriteSheetLoader::getInstance()->getSprite("Bomb", "Bomb_Placeholder");
	m_sprite->setPosition(parent->getBombSpawnPoint());

	m_yVel = 0.0f;
	m_xVel = 0.0f;

	m_bombBlastArea.setSize(sf::Vector2f(SettingsManager::getSettings()->ENEMY_GOBLIN_BOMB_BLAST_AREA_SIZE, SettingsManager::getSettings()->ENEMY_GOBLIN_BOMB_BLAST_AREA_SIZE));
	m_bombBlastArea.setFillColor(sf::Color::Yellow);

	m_bombHasBlasted = false;
	m_bombBlastCurrentTime = 0.0f;
	m_bombBlastTotalTime = SettingsManager::getSettings()->ENEMY_GOBLIN_BOMB_AOE_DURATION;

	m_animations = new AnimationManager(this);
	m_animations->addAnimation("GoblinBomb_falling_0", 1.0f, m_xPos, m_yPos);
	m_animations->setCurrentAnimation("GoblinBomb_falling_0");
}


EnemyBomb::~EnemyBomb()
{
}

void EnemyBomb::update(float delta)
{
	m_animations->update(m_xPos, m_yPos);
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
		m_sprite->setPosition(m_xPos, m_yPos);

		for(unsigned int a = 0; a < levelObjects.size(); a++)
		{
			if(collidesWith(levelObjects[a]))
			{
				//Spela up ljud här
				AudioMixer::getInstance()->removeSound(this);
				AudioMixer::getInstance()->playSound("Explosion_1", 0.0f, 0.0f, 100.0f, 100.0f, m_xPos, m_yPos, 1200.0f, 10.0f, 1.0f);
				m_bombHasBlasted = true;

				m_bombBlastArea.setPosition(m_sprite->getGlobalBounds().left + m_sprite->getGlobalBounds().width / 2.0f - m_bombBlastArea.getSize().x / 2.0f
					,m_sprite->getGlobalBounds().top + m_sprite->getGlobalBounds().height - m_bombBlastArea.getSize().y);

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
		window->draw(*m_animations->getCurrentSprite());
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
		return m_sprite->getGlobalBounds();
	}
}

bool EnemyBomb::collidesWith(LevelObject* levelObject)
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