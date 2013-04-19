#include "SpriteSheetLoader.h"

SpriteSheetLoader::SpriteSheetLoader(void)
{
}

SpriteSheetLoader::~SpriteSheetLoader(void)
{
	for(mapSurfacesIterator it = m_loadedSheets.begin();
		it != m_loadedSheets.end();
		++it)
	{
		delete it->second;
	}
}

SpriteSheet* SpriteSheetLoader::getSheet(string sheetUniqueName)
{
	mapSurfacesIterator keyIterator = m_loadedSheets.find(sheetUniqueName);

	if(keyIterator != m_loadedSheets.end())
	{
		return keyIterator->second;
	}
	else
	{
		SpriteSheet* sheetImage = loadSheet(sheetUniqueName);

		if(sheetImage != nullptr)
		{
			m_loadedSheets.insert(std::pair<std::string, SpriteSheet*>(sheetUniqueName, sheetImage));
			return sheetImage;
		}
		else
		{
			return nullptr;
		}
	}
}

SpriteSheet* SpriteSheetLoader::loadSheet(string sheetUniqueName)
{
	SpriteSheet* source = new SpriteSheet();
	
	bool loadSuccessfull = source->loadSpriteSheet(sheetUniqueName);

	if(loadSuccessfull)
	{
		return source;
	}
	else
	{
		delete source;
		return nullptr;
	}
}

sf::Sprite* SpriteSheetLoader::getSprite(std::string sheetUniqueName ,std::string spriteUniqueName)
{
	sf::Sprite* returnSprite = this->getSheet(sheetUniqueName)->getSprite(spriteUniqueName);

	if(returnSprite != nullptr)
	{
		return returnSprite;
	}
	else
	{
		return nullptr;
	}
}

sf::Sprite* SpriteSheetLoader::getSprite(sf::Sprite* sprite, std::string sheetUniqueName ,std::string spriteUniqueName)
{
	sf::Sprite* returnSprite = this->getSheet(sheetUniqueName)->getSprite(sprite, spriteUniqueName);

	if(returnSprite != nullptr)
	{
		return returnSprite;
	}
	else
	{
		return nullptr;
	}
}

SpriteSheetLoader* SpriteSheetLoader::getInstance()
{
	static SpriteSheetLoader instance;
	return &instance;
}