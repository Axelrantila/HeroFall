#include "AudioMixer.h"
#include "Game.h"
#include "GameOver.h"
#include "InputManager.h"
#include "Menus.h"
#include "SpriteSheetLoader.h"
#include "StateManager.h"

#include <iostream>

StateManager::StateManager()
{
	m_window = new sf::RenderWindow(
		sf::VideoMode(SettingsManager::getSettings()->FRAME_RESOLUTION_WINDOWED_X, SettingsManager::getSettings()->FRAME_RESOLUTION_WINDOWED_Y),
		SettingsManager::getSettings()->FRAME_TITLE);
	m_window->setMouseCursorVisible(false);
	m_window->setFramerateLimit(60);

	//Preload resources
	SpriteSheetLoader::getInstance()->getSheet("Background");

	m_states.push_back(new Menus());

	m_deltaTime = 0.0f;
	m_clock.restart();
}


StateManager::~StateManager()
{
	delete m_window;
	for(unsigned int a = 0; a < m_states.size(); a++)
	{delete m_states[a];}
}

void StateManager::addState(State* state)
{
	m_states.push_back(state);
}

void StateManager::run()
{
	m_running = true;

	while(m_running)
	{
		m_deltaTime = m_clock.getElapsedTime().asSeconds();
		m_clock.restart();

		//Handle events
		sf::Event windowEvent;
		while(m_window->pollEvent(windowEvent))
		{
			if(windowEvent.type == sf::Event::Closed)
			{m_running = false;}

			else if(windowEvent.type == sf::Event::KeyPressed)
			{InputManager::getInstance()->keyPressed(windowEvent.key.code);}
			
			else if(windowEvent.type == sf::Event::KeyReleased)
			{InputManager::getInstance()->keyReleased(windowEvent.key.code);}

			else{sendInputToCurrentState(windowEvent);}
		}

		if(!m_states.empty())
		{
			//Render state
			for(unsigned int a = 0; a < m_states.size(); a++)
			{
				State* currentState = m_states.at(a);

				if(currentState != nullptr)
				{
					if(currentState->getRunning())
					{
						m_window->clear();
						currentState->update(this, m_deltaTime);
						currentState->draw(m_window);
						m_window->display();
					}
				}
			}

			//Remove dead states
			for(int a = m_states.size() - 1; a >= 0; a--)
			{
				State* currentState = m_states.at(a);
				if(currentState->getMarkedForDeletion())
				{
					delete currentState;
					m_states.erase(m_states.begin() + a);
					m_window->setView(sf::View(sf::FloatRect(0.0f, 0.0f, (float)SettingsManager::getSettings()->FRAME_RESOLUTION_WINDOWED_X, (float)SettingsManager::getSettings()->FRAME_RESOLUTION_WINDOWED_Y)));
				}
			}

			//Add addition states
			while(!m_statesToAdd.empty())
			{
				if(m_statesToAdd[0] == STATE_MENUS)
				{m_states.push_back(new Menus());}

				else if(m_statesToAdd[0] == STATE_GAME)
				{m_states.push_back(new Game());}

				else if(m_statesToAdd[0] == STATE_GAMEOVER)
				{m_states.push_back(new GameOver());}

				m_statesToAdd.pop_back();
			}
		}
		else
		{
			m_running = false;
		}

		AudioMixer::getInstance()->update();
		InputManager::getInstance()->update();
	}
}

void StateManager::sendInputToCurrentState(sf::Event windowEvent)
{
	if(!m_states.empty())
	{
		State* currentState = m_states.at(m_states.size() - 1);

		if(currentState != nullptr &&
			currentState->getRunning())
		{
			currentState->handleEvents(windowEvent);
		}
	}
}

void StateManager::addState(StateType state)
{
	m_statesToAdd.push_back(state);
}