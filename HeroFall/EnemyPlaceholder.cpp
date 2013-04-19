#include "EnemyPlaceholder.h"

EnemyPlaceholder::EnemyPlaceholder(float xPos, float yPos)
	:Enemy(ENEMY_PLACEHOLDER, xPos, yPos, 65.0f)
{
	m_xVel = -125.0f;
	m_yVel = 0.0f;

	m_rect = new sf::RectangleShape();
	m_rect->setPosition(xPos, yPos);
	m_rect->setFillColor(sf::Color(13, 37, 57));
	m_rect->setSize(sf::Vector2f(93.0f, 93.0f));
}


EnemyPlaceholder::~EnemyPlaceholder()
{
	delete m_rect;
}

void EnemyPlaceholder::move(float delta)
{
	m_xPos += delta * m_xVel;
	m_rect->setPosition(m_xPos, m_rect->getPosition().y);
}


void EnemyPlaceholder::update(float delta)
{
}

void EnemyPlaceholder::draw(sf::RenderWindow* window)
{
	window->draw(*m_rect);
}

bool EnemyPlaceholder::collidesWith(LevelObject* levelObject)
{
	return true;
}