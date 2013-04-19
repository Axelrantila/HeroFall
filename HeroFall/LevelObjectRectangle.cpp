#include "LevelObjectRectangle.h"

#include <iostream>

#pragma region Contructors
LevelObjectRectangle::LevelObjectRectangle(float xPos, float yPos, float width, float height, sf::Color color)
	:LevelObject(PT_UPPER_LEFT, LO_RECTANGLE, xPos, yPos)
{
	m_width = width;
	m_height = height;

	m_rectangle = new sf::RectangleShape(sf::Vector2f(width, height));
	m_rectangle->setPosition(xPos, yPos);
	m_rectangle->setFillColor(color);
}

LevelObjectRectangle::~LevelObjectRectangle()
{
	delete m_rectangle;
}
#pragma endregion

#pragma region Publics
bool LevelObjectRectangle::collidesWith(LevelObject* anotherLevelObject)
{
	if(anotherLevelObject->getLevelObjectType() == LO_RECTANGLE)
	{
		sf::Vector2f otherSize = ((LevelObjectRectangle*)anotherLevelObject)->getSize();
		float otherXPos = ((LevelObjectRectangle*)anotherLevelObject)->getXPos();
		float otherYPos = ((LevelObjectRectangle*)anotherLevelObject)->getYPos();

		if(
			otherXPos > getXPos() + getSize().x
			|| otherXPos + otherSize.x < getXPos()
			|| otherYPos > getYPos() + getSize().y
			|| otherYPos + otherSize.y < getYPos()
			)
		{return false;}
		else {return true;}
	}

	return false;
}

void LevelObjectRectangle::draw(sf::RenderWindow* window)
{
	window->draw(*m_rectangle);
}

sf::Vector2f LevelObjectRectangle::getSize()
{
	return m_rectangle->getSize();
}
#pragma endregion