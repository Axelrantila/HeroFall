#ifndef ENEMYTROLL_H
#define ENEMYTROLL_H

#include "AnimationManager.h"
#include "Enemy.h"

#include <SFML\Graphics.hpp>

class EnemyTroll
	:public Enemy
{
public:
	EnemyTroll(float xPos, float yPos);
	~EnemyTroll();

	void update(float delta);
	void draw(sf::RenderWindow* window);

	sf::FloatRect getHitBox();

	bool collidesWith(LevelObject* levelObject);
	void takeDamage(float damage);

private:
	sf::Sprite* m_sprite;
	AnimationManager* m_animations;

	sf::Clock m_hitClock;
	float m_meleeHitTime;
	bool m_hitted;

	sf::RectangleShape* m_hitBoxTest;
};

#endif