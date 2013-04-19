#include "LevelManager.h"
#include "InputManager.h"
#include "SettingsManager.h"
#include "SpriteSheetLoader.h"

#include <iostream>

LevelManager::LevelManager(sf::View* view)
{
	m_view = view;
	m_levelObjects.push_back(new LevelObjectRectangle(0.0f, 400.0f, 125.0f, 125.0f, sf::Color::Blue));
	m_levelObjects.push_back(new LevelObjectRectangle(100.0f, 500.0f, 10000.0f, 100.0f, sf::Color::Magenta));
	m_player = new Player(200.0f, 200.0f);

	d_bg = SpriteSheetLoader::getInstance()->getSprite("DBG", "DBG_0");
	d_bg->setPosition(-1000.0f, -1000.0f);

	m_enemies = new std::vector<Enemy*>();
	m_enemies->push_back(new EnemyPlaceholder(1000.0f, 400.0f));
}

LevelManager::~LevelManager()
{
	for(unsigned int a = 0; a < m_levelObjects.size(); a++)
	{delete m_levelObjects[a];}
	delete m_player;

	for(unsigned int a = 0; a < m_enemies->size(); a++)
	{
		delete m_enemies->at(a);
	}
	delete m_enemies;
}

void LevelManager::draw(sf::RenderWindow* window)
{
	window->draw(*d_bg);

	for(unsigned int a = 0; a < m_levelObjects.size(); a++)
	{m_levelObjects[a]->draw(window);}

	for(unsigned int a = 0; a < m_enemies->size(); a++)
	{m_enemies->at(a)->draw(window);}

	m_player->draw(window);
}

void LevelManager::update(float deltaTime)
{
	//Move objects and check collision between enemies and the world
	m_player->update(deltaTime);
	m_player->move(deltaTime, m_levelObjects);

	//Check collision between the enemies and the player
	m_player->collidesWith(m_enemies);

	//Update the camera's view
	m_view->setCenter(m_player->getCenter());
}

void LevelManager::updatePlayerSpeed()
{
	//Update player speed

	if(InputManager::getInstance()->isKeyPressed("P1_MOVE_UP"))
	{
		m_player->increaseSpeed(0.0f, SettingsManager::getSettings()->PLAYER_SPEED_JUMP);
	}

	else if(InputManager::getInstance()->isKeyDown("P1_MOVE_DOWN"))
	{
		m_player->increaseSpeed(0.0f, SettingsManager::getSettings()->PLAYER_SPEED_DOWN);
	}

	if(InputManager::getInstance()->isKeyDown("P1_MOVE_LEFT")
		&& !InputManager::getInstance()->isKeyDown("P1_MOVE_RIGHT"))
	{
		m_player->setXSpeed(-SettingsManager::getSettings()->PLAYER_SPEED_SIDE);
	}

	else if(InputManager::getInstance()->isKeyDown("P1_MOVE_RIGHT")
		&& !InputManager::getInstance()->isKeyDown("P1_MOVE_LEFT"))
	{
		m_player->setXSpeed(SettingsManager::getSettings()->PLAYER_SPEED_SIDE);
	}

	else
	{
		m_player->haltXSpeed();
	}
}

bool LevelManager::playerIsDead()
{
	return m_player->isDead();
}