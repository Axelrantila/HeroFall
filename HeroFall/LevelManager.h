#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <SFML\Graphics.hpp>

#include "EnemyGoblin.h"
#include "EnemyPlaceholder.h"
#include "EnemyTroll.h"
#include "LevelObjectRectangle.h"
#include "Player.h"

class LevelManager
{
public:
	LevelManager(sf::View* view);
	~LevelManager();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void setPlayerSpeed(float xVel, float yVel);
	void updatePlayerSpeed();

	bool playerIsDead();

private:
	sf::View* m_view;

	Player*  m_player;
	std::vector<LevelObject*> m_levelObjects;
	std::vector<Enemy*>* m_enemies;

	sf::Sprite* d_bg;
};

#endif