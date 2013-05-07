#ifndef ENEMYPROJECTILE_H
#define ENEMYPROJECTILE_H

#include "AnimationManager.h"
#include "Enemy.h"
#include "EnemyShooter.h"

class EnemyProjectile
	:public Enemy
{
public:
	EnemyProjectile(EnemyShooter* parent);
	~EnemyProjectile();

	void move(float delta, std::vector<LevelObject*> levelObjects);
	void update(float delta);
	void draw(sf::RenderWindow* window);
	bool collidesWith(LevelObject* levelObject);

	sf::FloatRect getGlobalBounds();

private:
	AnimationManager* m_animations;
};

#endif