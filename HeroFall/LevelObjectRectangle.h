#ifndef LEVELOBJECTRECTANGLE_H
#define LEVELOBJECTRECTANGLE_H

#include "LevelObject.h"

class LevelObjectRectangle
	:public LevelObject
{
public:
	LevelObjectRectangle(float xPos, float yPos, float width, float height, sf::Color color);
	~LevelObjectRectangle();

	bool collidesWith(LevelObject* anotherLevelObject);
	void draw(sf::RenderWindow* window);

	sf::Vector2f getSize();

	sf::RectangleShape* getRectangle() {return m_rectangle;}

private:
	float m_width;
	float m_height;

	sf::RectangleShape* m_rectangle;
};

#endif