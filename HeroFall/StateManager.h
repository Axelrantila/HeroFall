#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"

#include <SFML\Graphics.hpp>
#include <vector>

enum StateType
{
	STATE_MENUS,
	STATE_GAME,
	STATE_GAMEOVER,
	STATE_GAMEOVER_VICTORY
};


class StateManager
{
public:
	StateManager();
	~StateManager();

	void run();
	void addState(State* state);
	void addState(StateType state);
	void sendInputToCurrentState(sf::Event windowEvent);

private:
	bool m_running;
	std::vector<State*> m_states;
	sf::RenderWindow* m_window;
	std::vector<StateType> m_statesToAdd;

	sf::Clock m_clock;
	float m_deltaTime;
};

#endif