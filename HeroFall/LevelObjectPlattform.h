#ifndef LEVELOBJECTPLATTFORM_H
#define LEVELOBJECTPLATTFORM_H

#include "levelobject.h"

class LevelObjectPlattform :
	public LevelObject
{
public:
	LevelObjectPlattform(float xPos, float yPos);
	~LevelObjectPlattform();

	 bool collidesWith(LevelObject* anotherLevelObject);
	 void draw(sf::RenderWindow* window);

private:
	sf::Sprite* m_sprite;
};

#endif