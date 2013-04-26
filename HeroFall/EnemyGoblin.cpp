#include "EnemyGoblin.h"


EnemyGoblin::EnemyGoblin(float xPos, float yPos, float health, float travelDistance)
	:Enemy(ENEMY_GOBLIN, xPos, yPos, health)
{
	m_xPos0 = xPos;
	m_xPos1 = xPos + travelDistance;

	m_animations = new AnimationManager(this);
	m_animations->addAnimation("Airship_Walk_0", 1.0f, xPos, yPos);
	m_animations->addAnimation("Airship_Walk_1", 1.0f, xPos, yPos);
	m_animations->setCurrentAnimation("Airship_Walk_0");

	m_xVel = 125.0f;
	m_yVel = 0.0f;
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
}

bool EnemyGoblin::collidesWith(LevelObject* levelObject)
{
	return false;
}

void EnemyGoblin::move(float delta, std::vector<LevelObject*> levelObjects)
{
	m_yPos += m_yVel * delta;

	if(m_xVel > 0.0f
		&& m_xPos + m_xVel * delta >= m_xPos1)
	{
		m_xVel *= -1.0f;
		m_animations->setCurrentAnimation("Airship_Walk_1");
	}
	else if(m_xVel < 0.0f
		&& m_xPos + m_xVel * delta <= m_xPos0)
	{
		m_xVel *= -1.0f;
		m_animations->setCurrentAnimation("Airship_Walk_0");
	}

	m_xPos += m_xVel * delta;
}