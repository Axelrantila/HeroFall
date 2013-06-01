#ifndef SPRITESHEETLOADER_H
#define SPRITESHEETLOADER_H

#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <string>
#include "SettingsManager.h"
#include "SpriteSheet.h"

typedef std::string string;
typedef std::unordered_map<string, SpriteSheet*> mapSurfaces;
typedef std::unordered_map<string, SpriteSheet*>::iterator mapSurfacesIterator;

class SpriteSheetLoader
{
private:
	mapSurfaces m_loadedSheets;
	SpriteSheetLoader();
	~SpriteSheetLoader();

public:
	static SpriteSheetLoader* getInstance();

	SpriteSheet* getSheet(string sheetUniqueName);
	SpriteSheet* loadSheet(string sheetUniqueName);

	sf::Sprite* getSprite(std::string sheetUniqueName, std::string spriteUniqueName);
	sf::Sprite* getSprite(sf::Sprite* sprite, std::string sheetUniqueName, std::string spriteUniqueName);

	void removeSheet(string sheetUniqueName);
	void removeAllSheets();

	bool isLoaded(std::string sheetName);
};

#endif