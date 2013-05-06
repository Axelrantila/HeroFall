#ifndef CHARACTER_H
#define CHARACTER_H

#include "gameobject.h"

class LevelObject;
namespace sf{class RenderWindow;};

enum DamageType
{
	DT_MELEE
};

class Character :
	public GameObject
{
public:
	Character(PositionType positionType, float xPos, float yPos, float health);
	virtual ~Character();

	virtual void move(float delta);
	virtual void update(float delta) = 0;
	virtual void applyGravity(float delta);
	virtual void draw (sf::RenderWindow* window) = 0;

	virtual bool collidesWith(LevelObject* levelObject) = 0;
	virtual float getGravityDistance(float delta);

	virtual bool isDead();
	virtual void takeDamage(float damage);

protected:
	float m_gravityConstant;
	float m_xVel;
	float m_yVel;

	bool m_isDead;
	float m_health;
	float m_armor;
};

#endif