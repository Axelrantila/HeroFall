#include "GameObject.h"


GameObject::GameObject(PositionType positionType, float xPos, float yPos)
{
	m_positionType = positionType;
	m_xPos = xPos;
	m_yPos = yPos;
}

GameObject::~GameObject()
{
}