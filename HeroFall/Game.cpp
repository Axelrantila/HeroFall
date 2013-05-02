#include "AudioMixer.h"
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
		sf::Vector2f((float)SettingsManager::getSettings()->FRAME_RESOLUTION_WINDOWED_X * 1.0f, (float)SettingsManager::getSettings()->FRAME_RESOLUTION_WINDOWED_Y * 1.0f));
	m_levelManager = new LevelManager(m_view);


	AudioMixer::getInstance()->playMusic("The_Forest_Awakes", 0.0f, 10.0f, 10.0f, true);
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
			AudioMixer::getInstance()->stopMusic();
			//Lägg till death screen statet här.
			stateManager->addState(STATE_GAMEOVER);
		}
}

void Game::draw(sf::RenderWindow* window)
{
	m_levelManager->draw(window);
}

void Game::handleEvents(sf::Event windowEvent)
{
}