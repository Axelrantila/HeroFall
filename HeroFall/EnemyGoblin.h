#ifndef ENEMYGOBLIN_H
#define ENEMYGOBLIN_H

#include "AnimationManager.h"
#include "Enemy.h"

class EnemyGoblin
	:public Enemy
{
public:
	EnemyGoblin(float xPos, float yPos, float health, float travelDistance);
	~EnemyGoblin();

	void update(float delta);
	void draw(sf::RenderWindow* window);
	bool collidesWith(LevelObject* levelObject);
	void move(float delta, std::vector<LevelObject*> levelObjects);

	sf::Vector2f getBombSpawnPoint();

private:
	float m_xPos0;
	float m_xPos1;

	AnimationManager* m_animations;
};

#endif