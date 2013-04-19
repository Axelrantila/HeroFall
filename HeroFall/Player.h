#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"
#include "character.h"

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

private:
	sf::Sprite* m_rect;
	sf::Sprite* m_swordRect;

	bool m_swordIsSwinging;
	bool m_swordHasHittedEnemy;
	sf::Clock m_swordClock;
	float m_targetSwingTime;

	bool m_markedForHalt;

	Animation* d_testAnim;

	sf::Clock m_meleeHitClock;
	float m_meleeHitTime;
};

#endif