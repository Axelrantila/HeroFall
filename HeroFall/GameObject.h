#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

enum PositionType
{
	PT_UPPER_LEFT,
	PT_CENTER
};

class GameObject
{
public:
	GameObject(PositionType positionType, float xPos, float yPos);
	virtual ~GameObject();

	float getXPos() {return m_xPos;}
	float getYPos() {return m_yPos;}

	void setXPos(float xPos) {m_xPos = xPos;}
	void setYPos(float yPos) {m_yPos = yPos;}

protected:
	PositionType m_positionType;

	float m_xPos;
	float m_yPos;
};

#endif