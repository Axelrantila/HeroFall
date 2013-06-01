#include "EnemyGoblin.h"
#include "ScoreManager.h"
#include "SettingsManager.h"
#include "SpriteSheetLoader.h"

EnemyGoblin::EnemyGoblin(float xPos, float yPos, float travelDistance)
	:Enemy(ENEMY_GOBLIN, xPos, yPos, SettingsManager::getSettings()->ENEMY_GOBLIN_HEALTH)
{
	m_normalDirection = DIR_RIGHT;
	m_direction = DIR_RIGHT;

	m_xPos0 = xPos;
	m_xPos1 = xPos + travelDistance;

	if(!SpriteSheetLoader::getInstance()->isLoaded("AirshipAttack"))
	{
		sf::sleep(sf::seconds(2.0f));
	}

	m_animations = new AnimationManager(this);
	m_animations->addAnimation("AirshipAttack_Attack_0", SettingsManager::getSettings()->ENEMY_GOBLIN_BOMB_SPAWN_TIME, xPos, yPos);
	m_animations->addAnimation("Airship_Die_0", m_deathTime, xPos, yPos);
	m_animations->setCurrentAnimation("AirshipAttack_Attack_0");

	m_xVel = SettingsManager::getSettings()->ENEMY_GOBLIN_SPEED_SIDE;
	m_yVel = 0.0f;

	m_bombSpawnTime = SettingsManager::getSettings()->ENEMY_GOBLIN_BOMB_SPAWN_TIME;
	m_clock.restart();
}


EnemyGoblin::~EnemyGoblin(void)
{
	delete m_animations;
}

void EnemyGoblin::draw(sf::RenderWindow* window)
{
	window->draw(*m_animations->getCurrentSprite());
}

void EnemyGoblin::update(float update)
{
	m_animations->update(m_xPos, m_yPos);

	if(m_isDying)
	{
		if(!m_animations->isCurrentAnimation("Airship_Die_0"))
		{
			m_dyingClock.restart();
			m_animations->setCurrentAnimation("Airship_Die_0");
			ScoreManager::getInstance()->addScore(KILL_SHOOTER);
		}
		if(m_dyingClock.getElapsedTime().asSeconds() > m_deathTime)
		{
			m_isDead = true;
		}
	}
}

bool EnemyGoblin::collidesWith(LevelObject* levelObject)
{
	return false;
}

void EnemyGoblin::move(float delta, std::vector<LevelObject*> levelObjects)
{
	if(m_isDying)
	{return;}

	m_yPos += m_yVel * delta;

	if(m_xVel > 0.0f
		&& m_xPos + m_xVel * delta >= m_xPos1)
	{
		m_xVel *= -1.0f;
		m_direction = DIR_LEFT;
	}
	else if(m_xVel < 0.0f
		&& m_xPos + m_xVel * delta <= m_xPos0)
	{
		m_xVel *= -1.0f;
		m_direction = DIR_RIGHT;
	}

	m_xPos += m_xVel * delta;

	m_animations->setCurrentAnimation("AirshipAttack_Attack_0", m_direction);
}

sf::Vector2f EnemyGoblin::getBombSpawnPoint()
{
	return sf::Vector2f(m_animations->getCurrentSprite()->getGlobalBounds().left + m_animations->getCurrentSprite()->getGlobalBounds().width / 2.0f,
		m_animations->getCurrentSprite()->getGlobalBounds().top + m_animations->getCurrentSprite()->getGlobalBounds().height);
}

bool EnemyGoblin::shouldSpawnBomb()
{
	if(m_isDying){return false;}

	if(m_clock.getElapsedTime().asSeconds() >= m_bombSpawnTime)
	{
		m_clock.restart();
		return true;
	}

	return false;
}

sf::FloatRect EnemyGoblin::getGlobalBounds()
{
	return m_animations->getCurrentSprite()->getGlobalBounds();
}