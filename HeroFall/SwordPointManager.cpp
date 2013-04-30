#include "SwordPointManager.h"


SwordPointManager::SwordPointManager(Animation* parent, std::vector<SwordPointInfo> points)
{
	m_parent = parent;

	/*
	TODO

	Konventera om informationen i vektorn som man får in till en hitbox/sf::RectangleShape

	/TODO
	*/

	for(unsigned int a = 0; a < points.size(); a++)
	{
		sf::RectangleShape* hitBox = new sf::RectangleShape(points[a].size);
		hitBox->setRotation(points[a].rotation);
		hitBox->setOrigin(points[a].origin);
		hitBox->setPosition(points[a].position);
		hitBox->setFillColor(sf::Color(191, 255, 0));

		m_localPositions.push_back(points[a].position);
		m_points .push_back(points[a]);
		m_hitBoxes.push_back(hitBox);
	}
}


SwordPointManager::~SwordPointManager()
{
	for(unsigned int a = 0; a < m_hitBoxes.size(); a++)
	{delete m_hitBoxes[a];}
}

sf::RectangleShape* SwordPointManager::getHitbox(sf::Sprite* currentSprite)
{
	for(unsigned int a = 0; a < m_points.size(); a++)
	{
		if(m_points[a].sprite == currentSprite)
		{
			m_hitBoxes[a]->setPosition(currentSprite->getGlobalBounds().left + m_localPositions[a].x,
				currentSprite->getGlobalBounds().top + m_localPositions[a].y);


			return m_hitBoxes[a];
		}
	}

	return nullptr;
}