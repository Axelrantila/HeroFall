#ifndef ENEMYBASE_H
#define ENEMYBASE_H

#include "Enemy.h"

class AnimationManager;
class Player;

enum BaseAIState
{
	BASE_AI_WALKING_FORWARD,
	BASE_AI_WALKING_BACKWARD
};

class EnemyBase:
	public Enemy
{
public:
	EnemyBase(float xPos, float yPos, sf::View* view = nullptr);
	~EnemyBase();

	void update(float delta);
	void draw(sf::RenderWindow* window);
	bool collidesWith(LevelObject* levelObject);
	void move(float delta, std::vector<LevelObject*> levelObjects);
	void updateState(Player* player);

	sf::FloatRect getHitBox();
	sf::Vector2f getCenter();
	void takeDamage(float damage);

private:
	AnimationManager* m_animations;

	float m_timeDead;

	BaseAIState m_currentState;
	sf::Clock m_AIStateClock;
	float m_AIChangeLimit;
};

#endif