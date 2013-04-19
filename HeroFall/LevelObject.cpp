#include "LevelObject.h"


LevelObject::LevelObject(PositionType positionType, LevelObjectType type, float xPos, float yPos)
	:GameObject(positionType, xPos, yPos)
{
	m_levelObjectType = type;
}

LevelObject::~LevelObject()
{
}

LevelObjectType LevelObject::getLevelObjectType()
{
	return m_levelObjectType;
}