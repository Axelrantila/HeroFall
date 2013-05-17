#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

#include <SFML\Graphics.hpp>

enum EnemyType
{
	ENEMY_PLACEHOLDER,
	ENEMY_TROLL,
	ENEMY_GOBLIN,
	ENEMY_SHOOTER,
	ENEMY_BOMB,
	ENEMY_PROJECTILE,
	ENEMY_BASE
};

class Enemy :
	public Character
{
public:
	Enemy(EnemyType type, float xPos, float yPos, float health, sf::View* view = nullptr);
	virtual ~Enemy();

	virtual void move(float delta, std::vector<LevelObject*> levelObjects);
	virtual void update(float delta) = 0;
	virtual void applyGravity(float delta);
	virtual void draw (sf::RenderWindow* window) = 0;
								
	virtual float getGravityDistance(float delta);

	EnemyType getType(){return m_type;}

	virtual bool collidesWith(LevelObject* levelObject) = 0;

protected:
	float m_xVel;
	float m_yVel;

	float m_health;
	float m_armor;

	EnemyType m_type;

	sf::View* m_view;
	bool m_seen;
};

#endif