#ifndef ENEMYPROJECTILE_H
#define ENEMYPROJECTILE_H

#include "Enemy.h"

class AnimationManager;
class EnemyShooter;
class LevelManager;

class EnemyProjectile
	:public Enemy
{
public:
	EnemyProjectile(EnemyShooter* parent, LevelManager* levelManager);
	~EnemyProjectile();

	void move(float delta, std::vector<LevelObject*> levelObjects);
	void update(float delta);
	void draw(sf::RenderWindow* window);
	bool collidesWith(LevelObject* levelObject);

	sf::FloatRect getGlobalBounds();

private:
	AnimationManager* m_animations;
	LevelManager* m_levelManager;
	sf::Clock m_clock;
	float m_particleSpawnTime;
	sf::Clock m_lifeClock;
};

#endif