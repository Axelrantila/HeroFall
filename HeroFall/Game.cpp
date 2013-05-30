#include "AudioMixer.h"
#include "Game.h"
#include "InputManager.h"
#include "ScoreManager.h"
#include "SettingsManager.h"
#include "SpriteSheetLoader.h"
#include "Util.h"
#include "Player.h"

#include <iostream>

Game::Game(sf::RenderWindow*  window)
	:State()
{
	m_window = window;
	m_view = new sf::View(
		sf::Vector2f((float)SettingsManager::getSettings()->FRAME_VIEW_X / 2.0f, (float)SettingsManager::getSettings()->FRAME_VIEW_Y / 2.0f),
		sf::Vector2f((float)SettingsManager::getSettings()->FRAME_VIEW_X, (float)SettingsManager::getSettings()->FRAME_VIEW_Y));
	m_levelManager = new LevelManager(m_view, m_window);

	m_view->getCenter();
	m_view->getSize();

	sf::sleep(sf::seconds(6.0f));

	AudioMixer::getInstance()->playMusic("The_Forest_Awakes", 0.0f, 15.0f, 15.0f, true);
}


Game::~Game()
{	
	delete m_levelManager;
	delete m_view;
}

void Game::update(StateManager* stateManager, float delta)
{
	//Update
	m_levelManager->update(delta);
	m_levelManager->updatePlayerSpeed();
	

	if(m_levelManager->playerIsDead())
	{
		markForDeletion();
		AudioMixer::getInstance()->stopMusic();
		AudioMixer::getInstance()->playMusic("Game_Over", 0.0f, 70.0f, 70.0f, false);
		//L�gg till death screen statet h�r.
		if(ScoreManager::getInstance()->getScore() > SettingsManager::getSettings()->HIGHSCORE3_SCORE)
		{
			stateManager->addState(STATE_GAMEOVER_VICTORY);
		}
		else
		{
			stateManager->addState(STATE_GAMEOVER);
		}
	}
	
	/*if(m_levelManager->getPlayer()->getXPos() > 36320)
	{ stateManager->addState(STATE_GAMEOVER_VICTORY); }*/
}

void Game::draw(sf::RenderWindow* window)
{
	m_levelManager->draw(window);
}

void Game::handleEvents(sf::Event windowEvent)
{
}