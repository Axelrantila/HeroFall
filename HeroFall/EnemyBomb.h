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

private:
	EnemyGoblin* m_parent;

	sf::Sprite* d_sprite;
};

#endif