#ifndef MENUS_H
#define MENUS_H

#include "SpriteSheetLoader.h"
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
{
public:
	Menus(sf::RenderWindow* window);
	~Menus(void);

	void Update(sf::Time deltaTime);
	void Draw(sf::RenderWindow *window);
	Menu currentState;

private:
	UIButton* Play;
	UIButton* Options;
	UIButton* Credits;
	UIButton* Quit;
	UIButton* Return;
	int tracker;
	sf::Sprite *background;
};

#endif

