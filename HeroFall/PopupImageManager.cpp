#include "PopupImageManager.h"
#include "SpriteSheetLoader.h"

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Sprite.hpp>

PopupImageManager::PopupImageManager()
{
}


PopupImageManager::~PopupImageManager()
{
	for(unsigned int a = 0; a < m_images.size(); a++)
	{
		delete m_images[a].sprite;
	}
}

void PopupImageManager::addImage(std::string sheetName, std::string spriteName, sf::Vector2f position, sf::Vector2f speed, float maxTime)
{
	PopupImage image;
	image.sprite = new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite(sheetName, spriteName));
	image.sprite->setPosition(position);
	image.speed = speed;
	image.maxTime = maxTime;
	image.currentTime = 0.0f;
	image.markedForDelete = false;

	m_images.push_back(image);
}

void PopupImageManager::update(float delta)
{
	for(unsigned int a = 0; a < m_images.size(); a++)
	{
		m_images[a].currentTime += delta;
		m_images[a].sprite->setColor(sf::Color(255, 255, 255, 255 - (sf::Uint8)((m_images[a].currentTime/m_images[a].maxTime) * 255.0f)));
		m_images[a].sprite->setPosition(m_images[a].sprite->getPosition() + m_images[a].speed * delta);

		if(m_images[a].currentTime >= m_images[a].maxTime)
		{m_images[a].markedForDelete = true;}
	}

	if(!m_images.empty())
	{
		for(unsigned int a = m_images.size() - 1; a >= 0; a--)
		{
			if(m_images[a].markedForDelete)
			{
				delete m_images[a].sprite;
				m_images.erase(m_images.begin() + a);
			}

			if(a == 0){break;}
		}
	}
}

void PopupImageManager::draw(sf::RenderWindow* window)
{
	for(unsigned int a = 0; a < m_images.size(); a++)
	{
		window->draw(*m_images[a].sprite);
	}
}