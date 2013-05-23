#ifndef ENEMYSHOOTER_H
#define ENEMYSHOOTER_H

#include "Enemy.h"
#include "LevelObjectRectangle.h"

class AnimationManager;
class Player;

class EnemyShooter :
	public Enemy
{
public:
	EnemyShooter(float xPos, float yPos, float health, Player* player, CharacterDirection direction, sf::View* view = nullptr);
	~EnemyShooter();

	bool canShoot();
	sf::Vector2f getProjectileSpawnPoint();
	sf::Vector2f getProjectileSpeed();

	void update(float delta);
	void draw(sf::RenderWindow* window);
	bool collidesWith(LevelObject* levelObject);
	
	sf::FloatRect getGlobalBounds();

private:
	AnimationManager* m_animations;

	sf::Clock m_shootClock;
	float m_shootTime;
	bool m_canShoot;
	Player* m_player;
};

#endif 