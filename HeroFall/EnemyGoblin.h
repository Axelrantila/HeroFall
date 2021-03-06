#ifndef ENEMYGOBLIN_H
#define ENEMYGOBLIN_H

#include "AnimationManager.h"
#include "Enemy.h"

class EnemyGoblin
	:public Enemy
{
public:
	EnemyGoblin(float xPos, float yPos, float travelDistance);
	~EnemyGoblin();

	void update(float delta);
	void draw(sf::RenderWindow* window);
	bool collidesWith(LevelObject* levelObject);
	void move(float delta, std::vector<LevelObject*> levelObjects);

	sf::Vector2f getBombSpawnPoint();
	bool shouldSpawnBomb();
	sf::FloatRect getGlobalBounds();

private:
	float m_xPos0;
	float m_xPos1;

	AnimationManager* m_animations;

	sf::Clock m_clock;
	float m_bombSpawnTime;

	sf::RectangleShape m_hitbox;
};

#endif