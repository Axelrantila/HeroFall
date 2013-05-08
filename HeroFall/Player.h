#ifndef PLAYER_H
#define PLAYER_H

#include "AnimationManager.h"
#include "Character.h"

#include <SFML\Graphics.hpp>

class Enemy;
class LevelObject;
class LevelManager;

//TYPES OF ATTACKS
enum  AttackType
{
	ATTACK_NORMAL,
	ATTACK_COMBO_0
};

enum JumpStage
{
	JUMPING_UPWARDS,
	JUMPING_FALLING,
	JUMPING_LANDING
};

class Player :
	public Character
{
public:
	Player(float xPos, float yPos, LevelManager* levelManager);
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
	void swingSword(AttackType type = ATTACK_NORMAL);
	void block(bool blocking);
	void takeDamage(float damage);

	bool isOnGround() {return m_isOnGround;}

private:
	AnimationManager* m_animations;
	sf::RectangleShape* m_hitBox;
	std::vector<sf::RectangleShape*> m_swordBoxes;
	sf::RectangleShape* m_shieldBox;

	std::map<Animation*, sf::RectangleShape> m_swordBoxesMap;

	bool m_swordIsSwinging;
	bool m_swordHasHittedEnemy;
	sf::Clock m_swordClock;
	float m_targetSwingTime;
	unsigned int m_currentAttack;
	bool m_isBlocking;

	bool m_markedForHalt;
	sf::Clock m_meleeHitClock;
	float m_meleeHitTime;
	bool m_hitted;

	bool m_isOnGround;
	bool m_groundMarked;
	bool m_isIdle;

	bool m_jumping;
	JumpStage m_currentJumpStage;

	LevelManager* m_levelManager;

	void updateBoxes();
};

#endif