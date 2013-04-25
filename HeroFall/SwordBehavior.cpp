#include "SwordBehavior.h"


SwordBehavior::SwordBehavior(sf::Sprite* targetSprite, float totalTime)
{
	m_targetSprite = targetSprite;
	m_totalTime = totalTime;
}

SwordBehavior::~SwordBehavior()
{
}

void SwordBehavior::restart()
{
	m_clock.restart();
}