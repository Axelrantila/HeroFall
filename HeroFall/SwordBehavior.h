#ifndef SWORDBEHAVIOR_H
#define SWORDBEHAVIOR_H

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Clock.hpp>

class SwordBehavior
{
public:
	SwordBehavior(sf::Sprite* targetSprite, float totalTime);
	virtual ~SwordBehavior();

	void restart();

	virtual void update() = 0;

protected:
	sf::Clock m_clock;
	float m_totalTime;
	sf::Sprite* m_targetSprite;
};

#endif