#ifndef GAMEOVERVICTORY_H
#define GAMEOVERVICTORY_H

#include "State.h"

#include <vector>

namespace sf
{
	class Sprite;
	class Text;
	class Font;
}

class GameOverVictory
	:public State
{
public:
	GameOverVictory();
	~GameOverVictory();

	void update(StateManager* stateManager, float deltaTime);
	void draw(sf::RenderWindow* window);
	void handleEvents(sf::Event windowEvent);

private:
	std::string m_letters;
	int m_currentLetter;

	sf::Sprite* m_bg;

	sf::Text* m_renderText;
	sf::Font* m_font;

	sf::Text* m_score1Text;
	sf::Text* m_score2Text;
	sf::Text* m_score3Text;

	int m_scoreToBeUpdated;
	/*
	0 = First place
	1 = Second place
	2 = Third place
	-1 = None
	*/
};

#endif