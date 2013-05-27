#ifndef GAMEOVERVICTORY_H
#define GAMEOVERVICTORY_H

#include "State.h"

namespace sf{class Sprite;}

class GameOverVictory
	:public State
{
public:
	GameOverVictory();
	~GameOverVictory();

	void update(StateManager* stateManager, float deltaTime);
	void draw(sf::RenderWindow* window);
	void handleEvents(sf::Event windowEvent){}

private:
	sf::Sprite* m_sprite;
};

#endif