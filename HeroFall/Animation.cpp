#include "Animation.h"
#include "GameObject.h"
#include "SpriteSheetLoader.h"

#include <iostream>
#include <fstream>

Animation::Animation(Character* parent, std::string name, float totalTime, float xPos, float yPos, bool shouldLockAtEnd)
{
	m_parent = parent;
	m_standardDirection = parent->getNormalDirection();
	m_mirrored = false;

	m_spriteBaseName = name;
	m_sheetName = m_spriteBaseName.substr(0, m_spriteBaseName.find_first_of("_"));

	//Load all sprites into the vector
	std::ifstream in("assets/Sprites/" + m_sheetName + "_anim.txt");

	if(in.is_open())
	{
		while(!in.eof())
		{
			std::string line;
			std::getline(in, line);

			if(line.substr(0, line.find_last_of("_")) == m_spriteBaseName)
			{
				m_sprites.push_back(new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite(m_sheetName, line)));
				m_sprites[m_sprites.size() - 1]->setPosition(xPos, yPos);
				m_mirroredImages.insert(std::pair<sf::Sprite*, bool>(m_sprites[m_sprites.size()-1], false));
			}
		}
	}

	m_currentSprite = m_sprites[0];
	////////////////////////////////////////////////
	m_mirroredOffsetPosition.x = m_sprites[0]->getGlobalBounds().width;
	////////////////////////////////////////////////
	m_currentFrame = 0;
	m_totalFrames = m_sprites.size();
	m_frameTime = totalTime / (float)(m_totalFrames);
	m_totalTime = totalTime;
	m_playing = false;
	m_stopped = false;

	m_xPos = xPos;
	m_yPos = yPos;

	m_shouldLockAtEnd = shouldLockAtEnd;
}

Animation::~Animation()
{
	for(unsigned int a = 0; a < m_sprites.size(); a++)
	{delete m_sprites[a];}
}

void Animation::play(CharacterDirection direction)
{
	if(direction != DIR_NONE
		&& direction != m_standardDirection)
	{
		m_mirrored = true;
	}
	else
	{
		m_mirrored = false;
	}

	m_playing = true;
	m_stopped = false;
	m_currentFrame = 0;
	m_clock.restart();
}

void Animation::pause()
{
	m_playing = false;
}

void Animation::stop()
{
	m_playing = false;
	m_stopped = true;
	m_currentFrame = 0;
	m_clock.restart();
}

void Animation::update(float xPos, float yPos)
{
	//////////////////////////////////////////////////////////////////
	if(m_shouldLockAtEnd && m_currentFrame == m_totalFrames - 1)
	{
	}

	else if(m_clock.getElapsedTime().asSeconds() > m_frameTime)
	{
		float m_totalDeltaTime = m_clock.getElapsedTime().asSeconds();

		while(m_totalDeltaTime >= m_frameTime)
		{
			m_currentFrame++;
			if(m_currentFrame == m_totalFrames)
			{
				m_currentFrame = 0;
			}

			m_totalDeltaTime -= m_frameTime;
		}

		m_currentSprite = m_sprites[m_currentFrame];
		m_clock.restart();
	}
	/////////////////////////////////////////////////////////////
	if(m_mirrored)
	{
		xPos += m_mirroredOffsetPosition.x;

		if(!m_mirroredImages[m_currentSprite])
		{
			m_mirroredImages[m_currentSprite] = true;
			m_currentSprite->setScale(-1.0f, 1.0f);
		}
		if(m_parent->isATroll())
		{
			xPos += 50.0f;
		}
	}
	else
	{
		if(m_mirroredImages[m_currentSprite])
		{
			m_mirroredImages[m_currentSprite] = false;
			m_currentSprite->setScale(1.0f, 1.0f);
		}
	}

	for(unsigned int a = 0; a < m_sprites.size(); a++)
	{m_sprites[a]->setPosition(xPos, yPos);}

	m_xPos = xPos;
	m_yPos = yPos;
}

sf::Sprite* Animation::getCurrentSprite()
{
	return m_currentSprite;
}

sf::Sprite* Animation::getSprite(unsigned int index)
{
	return m_sprites[index];
}

unsigned int Animation::getCurrentFrame()
{
	return m_currentFrame;
}