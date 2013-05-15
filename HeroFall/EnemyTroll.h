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
	TROLL_AI_ATTACK_0
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

private:
	AnimationManager* m_animations;

	sf::Clock m_hitClock;
	float m_meleeHitTime;
	bool m_hitted;

	sf::RectangleShape* m_hitBoxTest;

	TrollAIState m_currentAIState;
	sf::Clock m_AIStateClock;
	float m_AIChangeLimit;
};

#endif