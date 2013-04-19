#pragma once
#include <SFML\Graphics.hpp>

#include <string>

class Renderer;

typedef std::string string;

class Sprite
{
private:
	string m_sheetUniqueName;
	string m_spriteUniqueName;

	bool m_centered;

	sf::Sprite* m_sprite;

public:
	Sprite(void);
	Sprite(string sheetUniqueName, string spriteUniqueName, bool centered = false);
	~Sprite(void);

	string getSheetUniqueName() {	return m_sheetUniqueName;	};
	string getSpriteUniqueName()	{	return m_spriteUniqueName;	};
	sf::Sprite* getSprite()	{	return m_sprite;	};
	float getSpriteWidth()	{	return m_sprite->getLocalBounds().width;	};
	float getSpriteHeight()	{	return m_sprite->getLocalBounds().height;	};
	float getSpriteHalfWidth()	{	return m_sprite->getLocalBounds().width / 2.0f;	};
	float getSpriteHalfHeight()	{	return m_sprite->getLocalBounds().height / 2.0f;	};

	void setSprite(std::string sheetUniqueName);
	void setSprite(std::string sheetUniqueName, std::string spriteUniqueName);
};

