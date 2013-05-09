#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <SFML\Graphics.hpp>

#include "EnemyBomb.h"
#include "EnemyGoblin.h"
#include "EnemyPlaceholder.h"
#include "EnemyProjectile.h"
#include "EnemyShooter.h"
#include "EnemyTroll.h"
#include "HUD.h"
#include "LevelObjectRectangle.h"
#include "ParticleSystem.h"
#include "Player.h"

class LevelManager
{
public:
	LevelManager(sf::View* view, sf::RenderWindow* window);
	~LevelManager();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
	void addParticles(sf::Vector2f position, unsigned int particles, ParticleColor color = PARTICLE_COLOR_RED);

	void setPlayerSpeed(float xVel, float yVel);
	void updatePlayerSpeed();
	bool playerIsDead();

	void  cleanResources();

private:
	sf::RenderWindow* m_window;
	sf::View* m_view;
	HUD* m_HUD;

	Player*  m_player;
	std::vector<LevelObject*> m_levelObjects;
	std::vector<Enemy*>* m_enemies;

	sf::Sprite* d_bg;
	sf::Sprite* d_bg1;
	sf::Sprite* levelBlock1;
	sf::Sprite* levelBlock2;
	sf::Sprite* levelBlock3;
	sf::Sprite* levelBlock4;
	sf::Sprite* levelBlock5;
	sf::Sprite* levelBlock5_1;
	sf::Sprite* levelBlock5_2;
	sf::Sprite* levelBlock6;
	sf::Sprite* levelBlock7;
	sf::Sprite* levelBlock8;
	sf::Sprite* levelHouse;
	sf::Sprite* levelBridge;

	sf::Vector2f m_cameraMove;
	sf::Vector2f m_prevCameraCenter;

	std::vector<ParticleSystem*> m_particles;
};

#endif