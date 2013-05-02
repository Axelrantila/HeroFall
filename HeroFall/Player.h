#ifndef PLAYER_H
#define PLAYER_H

#include "AnimationManager.h"
#include "Character.h"

#include <SFML\Graphics.hpp>

class Enemy;
class LevelObject;

class Player :
	public Character
{
public:
	Player(float xPos, float yPos);
	~Player();

	void increaseSpeed(float xSpeed, float ySpeed);
	void setXSpeed(float xSpeed);
	void move(float delta, std::vector<LevelObject*> levelObjects);
	void update(float delta);
	void draw(sf::RenderWindow* window);
	void haltXSpeed();

	bool collidesWith(LevelObject* levelObject);
	void collidesWith(std::vector<Enemy*>* enemies);

	sf::Vector2f getCenter();
	void swingSword();

	void takeDamage(float damage);

	bool isOnGround() {return m_isOnGround;}

private:
	AnimationManager* m_animations;
	sf::RectangleShape* m_hitBox;
	std::vector<sf::RectangleShape*> m_swordBoxes;

	bool m_swordIsSwinging;
	bool m_swordHasHittedEnemy;
	sf::Clock m_swordClock;
	float m_targetSwingTime;
	unsigned int m_currentAttack;

	bool m_markedForHalt;
	sf::Clock m_meleeHitClock;
	float m_meleeHitTime;
	bool m_hitted;

	bool m_isOnGround;
	bool m_groundMarked;
	bool m_isIdle;

	void updateBoxes();
};

#endif