//#include "AudioMixer.h"
#include "Game.h"
#include "InputManager.h"
#include "SettingsManager.h"
#include "SpriteSheetLoader.h"
#include "Util.h"

#include "Menus.h"

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
}

void Game::update(StateManager* stateManager, float delta)
{
		//Update
		m_levelManager->updatePlayerSpeed();
		m_levelManager->update(delta);

		if(m_levelManager->playerIsDead())
		{
			markForDeletion();
			//Lägg till death screen statet här.
		}
}

void Game::draw(sf::RenderWindow* window)
{
	m_levelManager->draw(window);
}

void Game::handleEvents(sf::Event windowEvent)
{
}