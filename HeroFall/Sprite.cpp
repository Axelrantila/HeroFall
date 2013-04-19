#include <iostream>

#include "Sprite.h"
#include "SpriteSheetLoader.h"

Sprite::Sprite(void)
{
	m_sheetUniqueName = "devTemp";
	m_spriteUniqueName = "devTemp";
	m_centered = true;

	m_sprite = SpriteSheetLoader::getInstance()->getSprite(m_sheetUniqueName, m_spriteUniqueName);

	if (m_centered)
	{
		m_sprite->setOrigin(m_sprite->getLocalBounds().width / 2.0f, m_sprite->getLocalBounds().height / 2.0f);
	}
}

Sprite::Sprite(string sheetUniqueName, string spriteUniqueName, bool centered)
{
	m_sheetUniqueName = sheetUniqueName;
	m_spriteUniqueName = spriteUniqueName;
	m_centered = centered;

	//_sprite = ResourcesManager::getInstance()->getSpriteSheetLoader()->getSprite(_sheetUniqueName, _spriteUniqueName);

	if(m_sprite == nullptr)
	{
		std::cout << "Failed loading sprite " << sheetUniqueName << ", " << spriteUniqueName << std::endl;
		//_sprite = ResourcesManager::getInstance()->getSpriteSheetLoader()->getSprite("devTemp", "devTemp");
	}

	if (m_centered)
	{
		m_sprite->setOrigin(m_sprite->getLocalBounds().width / 2.0f, m_sprite->getLocalBounds().height / 2.0f);
	}
}

Sprite::~Sprite(void)
{
	delete m_sprite;
}

void Sprite::setSprite(std::string spriteUniqueName)
{
	this->setSprite(m_sheetUniqueName, spriteUniqueName);
}

void Sprite::setSprite(std::string sheetUniqueName, std::string spriteUniqueName)
{
	sf::Sprite* sprite = SpriteSheetLoader::getInstance()->getSprite(m_sprite, sheetUniqueName, spriteUniqueName);

	if(sprite != nullptr)
	{
		if (m_sprite != sprite)
		{
			delete m_sprite;
			m_sprite = nullptr;
		}

		m_sprite = sprite;
		m_sheetUniqueName = sheetUniqueName;
		m_spriteUniqueName = spriteUniqueName;
	}
}