#ifndef ENEMYTROLL_H
#define ENEMYTROLL_H

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

	sf::FloatRect getGlobalBounds();

	bool collidesWith(LevelObject* levelObject);

private:
	sf::Sprite* m_sprite;
};

#endif