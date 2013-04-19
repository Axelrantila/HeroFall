#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

#include <SFML\Graphics.hpp>

#include "GameObject.h"

enum LevelObjectType
{
	LO_RECTANGLE
};

class LevelObject
	:public GameObject
{
public:
	LevelObject(PositionType positionType, LevelObjectType type, float xPos, float yPos);
	virtual ~LevelObject();

	virtual bool collidesWith(LevelObject* anotherLevelObject) = 0;
	virtual void draw(sf::RenderWindow* window) = 0;

	sf::Color getPrimaryColor() {return m_primaryColor;}
	sf::Color getSecondaryColor() {return m_secondaryColor;}
	sf::Color getTritaryColor() {return m_tritaryColor;}

	void setPrimaryColor(sf::Color color) {m_primaryColor = color;}
	void setSecondayColor(sf::Color color) {m_secondaryColor = color;}
	void setTritaryColor(sf::Color color) {m_tritaryColor = color;}

	LevelObjectType getLevelObjectType();

protected:
	sf::Color m_primaryColor;
	sf::Color m_secondaryColor;
	sf::Color m_tritaryColor;

private:
	LevelObjectType m_levelObjectType;
};

#endif