#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>

#include "LevelManager.h"
#include "StateManager.h"

class Util;

class Game
	:public State
{
public:
	Game(sf::RenderWindow* window);
	~Game();

	void update(StateManager* stateManager, float m_deltaTime);
	void draw(sf::RenderWindow* window);
	void handleEvents(sf::Event windowEvent);

private:
	LevelManager* m_levelManager;
	sf::RenderWindow* m_window;
	sf::View* m_view;

	//sf::Clock m_clock;
	//float m_deltaTime;
};

#endif