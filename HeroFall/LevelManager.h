#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <SFML\Graphics.hpp>
#include <iostream>

#include "EnemyBase.h"
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
#include "PopupImageManager.h"

class LevelManager
{
public:
	LevelManager(sf::View* view, sf::RenderWindow* window);
	~LevelManager();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
	void addParticles(sf::Vector2f position, unsigned int particles, ParticleColor color = PARTICLE_COLOR_RED, float timeLimit = 5.0f);

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

	std::vector<sf::Sprite*> m_backgroundSprites;
	sf::Vector2f m_cameraMove;
	sf::Vector2f m_prevCameraCenter;

	std::vector<ParticleSystem*> m_particles;
	PopupImageManager* m_popupImages;
};

#endif