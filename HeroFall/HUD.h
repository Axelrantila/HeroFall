#ifndef HUD_H
#define HUD_H

#include "GameObject.h"
#include "Player.h"

#include <SFML\Graphics.hpp>

class HUD
	:public GameObject
{
public:
	HUD(sf::View* m_view, Player* player);
	~HUD();

	void update();
	void update(float delta);
	void draw(sf::RenderWindow* window);

private:
	sf::Sprite* m_GUI;
	sf::Sprite* m_healthbar;
	sf::Sprite* m_combobar;
	sf::View* m_view;

	sf::Font* m_font;
	sf::Text* m_text;

	float m_playerMaxHealth;
	Player* m_player;
};

#endif