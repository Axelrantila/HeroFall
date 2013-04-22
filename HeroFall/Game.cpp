//#include "AudioMixer.h"
#include "Game.h"
#include "InputManager.h"
#include "SettingsManager.h"
#include "SpriteSheetLoader.h"
#include "Util.h"

#include <iostream>

Game::Game()
	:State()
{
	m_view = new sf::View(
		sf::Vector2f(SettingsManager::getSettings()->FRAME_RESOLUTION_WINDOWED_X / 2.0f, SettingsManager::getSettings()->FRAME_RESOLUTION_WINDOWED_Y / 2.0f),
		sf::Vector2f((float)SettingsManager::getSettings()->FRAME_RESOLUTION_WINDOWED_X, (float)SettingsManager::getSettings()->FRAME_RESOLUTION_WINDOWED_Y));
	m_levelManager = new LevelManager(m_view);

	d_sprite = SpriteSheetLoader::getInstance()->getSprite("DBG", "DBG_0");

}


Game::~Game()
{	
	delete m_levelManager;
	delete m_view;

	//Clean up singeltons
}

void Game::update(StateManager* stateManager, float delta)
{
		//std::cout << (1.0f/m_deltaTime) << std::endl;

		//Update
		//AudioMixer::getInstance()->update();
		m_levelManager->updatePlayerSpeed();
		m_levelManager->update(delta);

		if(m_levelManager->playerIsDead())
		{
			markForDeletion();
		}
}

void Game::draw(sf::RenderWindow* window)
{
	m_view->setCenter(m_view->getCenter().x, m_view->getCenter().y);
	window->setView(*m_view);
	m_levelManager->draw(window);
}

void Game::handleEvents(sf::Event windowEvent)
{
}