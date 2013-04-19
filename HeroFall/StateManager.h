#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"

#include <SFML\Graphics.hpp>
#include <vector>

class StateManager
{
public:
	StateManager();
	~StateManager();

	void run();
	void addState(State* state);
	void sendInputToCurrentState(sf::Event windowEvent);

private:
	bool m_running;
	std::vector<State*> m_states;
	sf::RenderWindow* m_window;
};

#endif