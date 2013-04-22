#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

enum EnemyType
{
	ENEMY_PLACEHOLDER,
	ENEMY_TROLL,
	ENEMY_GOBLIN,
	ENEMY_SHOOTER
};

class Enemy :
	public Character
{
public:
	Enemy(EnemyType type, float xPos, float yPos, float health);
	virtual ~Enemy();

	virtual void move(float delta);
	virtual void update(float delta) = 0;
	virtual void applyGravity(float delta);
	virtual void draw (sf::RenderWindow* window) = 0;

	virtual bool collidesWith(LevelObject* levelObject) = 0;
	virtual float getGravityDistance(float delta);

	EnemyType getType(){return m_type;}

protected:
	float m_gravityConstant;
	float m_xVel;
	float m_yVel;

	float m_health;
	float m_armor;

	EnemyType m_type;
};

#endif