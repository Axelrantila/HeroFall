#ifndef SwordPointManager_H
#define SwordPointManager_H

#include "Animation.h"

/*
IMPORTANT

The position MUST be relative to the Sprite's internal position.
It is NOT A GLOBAL POSITION
*/

struct SwordPointInfo
{
	sf::Vector2f position;
	sf::Vector2f size;
	float rotation;
	sf::Vector2f origin;
	sf::Sprite* sprite;
};

class SwordPointManager
{
public:
	SwordPointManager(Animation* parent, std::vector<SwordPointInfo> points);
	~SwordPointManager();

	sf::RectangleShape* getHitbox(sf::Sprite* m_currentSprite);

private:
	Animation* m_parent;
	std::vector<SwordPointInfo> m_points;
	std::vector<sf::RectangleShape*> m_hitBoxes;
	std::vector<sf::Vector2f> m_localPositions;
};

#endif