#ifndef MENUS_H
#define MENUS_H

#include "SpriteSheetLoader.h"
#include "State.h"
#include "UIButton.h"
#include <SFML/Graphics.hpp>

enum Menu
{
	MAIN,
	LVLSELECT,
	OPTIONS,
	PAUSE,
	CREDITS
};

class Menus
	:public State
{
public:
	Menus();
	~Menus(void);

	void update(StateManager* stateManager, float delta);
	void draw(sf::RenderWindow* window);
	void handleEvents(sf::Event windowEvent);
	Menu currentState;

private:
	sf::Sprite* background;
	UIButton* Play;
	UIButton* Options;
	UIButton* Credits;
	UIButton* Quit;
	UIButton* Return;
	int tracker;
};

#endif

