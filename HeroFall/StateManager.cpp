#include "Game.h"
#include "InputManager.h"
#include "Menus.h"
#include "SpriteSheetLoader.h"
#include "StateManager.h"

StateManager::StateManager()
{
	m_window = new sf::RenderWindow(sf::VideoMode(SettingsManager::getSettings()->FRAME_RESOLUTION_WINDOWED_X, SettingsManager::getSettings()->FRAME_RESOLUTION_WINDOWED_Y), "MMO Experiance");
	m_window->setMouseCursorVisible(false);

	//Preload resources
	SpriteSheetLoader::getInstance()->getSheet("DBG");

	m_states.push_back(new Game());

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

			//Update stuff

			//Remove dead states
			for(int a = m_states.size() - 1; a >= 0; a--)
			{
				State* currentState = m_states.at(a);
				if(currentState->getMarkedForDeletion())
				{
					delete currentState;
					m_states.erase(m_states.begin() + a);
				}
			}
		}
		else
		{
			m_running = false;
		}

	}

	InputManager::getInstance()->update();
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