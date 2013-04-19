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
	m_view = new sf::View(sf::Vector2f(800.0f / 2.0f, 800.0f / 2.0f), sf::Vector2f(800.0f, 800.0f));
	m_levelManager = new LevelManager(m_view);

	d_sprite = SpriteSheetLoader::getInstance()->getSprite("DBG", "DBG_0");

	m_deltaTime = 0.0f;
}


Game::~Game()
{	
	delete m_levelManager;
	delete m_view;

	//Clean up singeltons
}

void Game::run()
{
	m_clock.restart();
	
}

void Game::update(StateManager* stateManager)
{
		m_deltaTime = m_clock.getElapsedTime().asSeconds();
		m_clock.restart();
		
		std::cout << (1.0f/m_deltaTime) << std::endl;

		//Update
		//AudioMixer::getInstance()->update();
		m_levelManager->updatePlayerSpeed();
		m_levelManager->update(m_deltaTime);

		if(m_levelManager->playerIsDead())
		{
			markForDeletion();
		}

		InputManager::getInstance()->update();
}

void Game::draw(sf::RenderWindow* window)
{
	window->clear();
	m_view->setCenter(m_view->getCenter().x, m_view->getCenter().y);
	window->setView(*m_view);
	m_levelManager->draw(window);
	window->display();
}

void Game::handleEvents(sf::Event windowEvent)
{
	if(windowEvent.type == sf::Event::KeyPressed)
	{
		InputManager::getInstance()->keyPressed(windowEvent.key.code);
	}
	else if(windowEvent.type == sf::Event::KeyReleased)
	{
		InputManager::getInstance()->keyReleased(windowEvent.key.code);
	}
}