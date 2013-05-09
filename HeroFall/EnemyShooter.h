#ifndef ENEMYSHOOTER_H
#define ENEMYSHOOTER_H

#include "Enemy.h"
#include "LevelObjectRectangle.h"

class AnimationManager;

class EnemyShooter :
	public Enemy
{
public:
	EnemyShooter(float xPos, float yPos, float health, sf::View* view = nullptr);
	~EnemyShooter();

	bool canShoot();
	sf::Vector2f getProjectileSpawnPoint();

	void update(float delta);
	void draw(sf::RenderWindow* window);
	bool collidesWith(LevelObject* levelObject);
	
	sf::FloatRect getGlobalBounds();

private:
	AnimationManager* m_animations;

	sf::Clock m_shootClock;
	float m_shootTime;
};

#endif 