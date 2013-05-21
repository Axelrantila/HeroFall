#ifndef ENEMYTROLL_H
#define ENEMYTROLL_H

#include "AnimationManager.h"
#include "Enemy.h"

#include <SFML\Graphics.hpp>

class Player;

enum TrollAIState
{
	TROLL_AI_WALKING_FORWARD,
	TROLL_AI_WALKING_BACKWARD,
	TROLL_AI_ATTACK_0,
	TROLL_AI_ATTACK_1
};

class EnemyTroll
	:public Enemy
{
public:
	EnemyTroll(float xPos, float yPos, sf::View* view = nullptr);
	~EnemyTroll();

	void update(float delta);
	void updateState(Player* player);
	void draw(sf::RenderWindow* window);
	void move(float delta, std::vector<LevelObject*> levelObjects);

	sf::FloatRect getHitBox();
	sf::Vector2f getCenter();

	bool collidesWith(LevelObject* levelObject);
	void takeDamage(float damage);
	sf::FloatRect getAttackHitbox();

private:
	AnimationManager* m_animations;

	//Being hit
	sf::Clock m_hitClock;
	float m_meleeHitTime;
	bool m_hitted;
	sf::RectangleShape* m_hitBoxTest;

	//AI
	TrollAIState m_currentAIState;
	sf::Clock m_AIStateClock;
	float m_AIChangeLimit;

	//Attacking
	sf::Clock m_attackClock;
	float m_attackStage1Time;
	float m_attackStage2Time;
};

#endif