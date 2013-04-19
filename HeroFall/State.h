#ifndef STATE_H
#define STATE_H

class StateManager;
namespace sf{class RenderWindow;}
#include <SFML\Window\Event.hpp>

class State
{
public:
	State() {m_running = true; m_markedForDeletion = false;}
	virtual ~State() {}

	virtual void pause() {m_running = false;}
	virtual void resume() {m_running = true;}
	virtual bool getRunning() {return m_running;}

	virtual void markForDeletion() {m_markedForDeletion = true;}
	virtual bool getMarkedForDeletion() {return m_markedForDeletion;}

	virtual void update(StateManager* stateManager) = 0;
	virtual void draw(sf::RenderWindow* window) = 0;
	virtual void handleEvents(sf::Event windowEvent) = 0;

protected:
	bool m_running;
	bool m_markedForDeletion;
};

#endif