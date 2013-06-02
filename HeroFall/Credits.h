#ifndef CREDITS_H
#define CREDITS_H

#include "State.h"

#include <SFML\Graphics.hpp>
#include "StateManager.h"

class Credits
	:public State
{
public:
	Credits();
	~Credits();

	void update(StateManager* stateManager, float deltaTime);
	void draw(sf::RenderWindow* window);
	void handleEvents(sf::Event windowEvent){}

private:
	sf::Sprite* m_sprite;
};

#endif