#ifndef ENEMYPLACEHOLDER_H
#define ENEMYPLACEHOLDER_H

#include <SFML\Graphics.hpp>

#include "Enemy.h"

class EnemyPlaceholder :
	public Enemy
{
public:
	EnemyPlaceholder(float xPos, float yPos);
	~EnemyPlaceholder();

	void move(float delta);
	void update(float delta);
	void draw (sf::RenderWindow* window);
	bool collidesWith(LevelObject* levelObject);

	sf::RectangleShape* getRect(){return m_rect;}

private:
	sf::RectangleShape* m_rect;
};

#endif