#include "SwordBehaviorUpAndDown.h"


SwordBehaviorUpAndDown::SwordBehaviorUpAndDown(sf::Sprite* targetSprite, float totalTime)
	:SwordBehavior(targetSprite, totalTime)
{
}

SwordBehaviorUpAndDown::~SwordBehaviorUpAndDown()
{
}

void SwordBehaviorUpAndDown::update()
{
	if(m_clock.getElapsedTime().asSeconds()  < (m_totalTime / 2.0f))
		{
			m_targetSprite->setRotation(360.0f -
				(m_clock.getElapsedTime().asSeconds() / (m_totalTime * 0.5f)) * 90.0f
				);
		}
		else
		{
			m_targetSprite->setRotation(
				270.0f + ((m_clock.getElapsedTime().asSeconds() - (m_totalTime * 0.5f)) / (m_totalTime * 0.5f)) * 90.0f
				);
		}
}