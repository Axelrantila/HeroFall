#ifndef ENEMYBOMB_H
#define ENEMYBOMB_H

#include "Enemy.h"

class EnemyGoblin;

class EnemyBomb
	:public Enemy
{
public:
	EnemyBomb(EnemyGoblin* parent);
	~EnemyBomb();

	void move(float delta, std::vector<LevelObject*> levelObjects);
	void update(float delta){}
	void draw(sf::RenderWindow* window);
	bool collidesWith(LevelObject* levelObject);

	sf::FloatRect getGlobalBounds();

private:
	sf::Sprite* d_sprite;
};

#endif