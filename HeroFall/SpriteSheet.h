#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <vector>
#include <string>
#include <SFML\Graphics.hpp>

#include "SettingsManager.h"

class SpriteSheet
{
public:
	SpriteSheet();
	~SpriteSheet();

	bool loadSpriteSheet(std::string spriteSheetName);

	sf::Sprite* getSprite(std::string name);
	sf::Sprite* getSprite(sf::Sprite* sprite, std::string name);

private:
	unsigned int m_wSheet;
	unsigned int m_hSheet;
	unsigned int m_wSprite;
	unsigned int m_hSprite;

	std::vector<std::string> m_spriteList;	// Inneh�ller alla sprites str�ngnamn i den ordning de l�ses in
	sf::Texture* m_spriteSheet;
};

#endif