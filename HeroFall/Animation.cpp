#include "Animation.h"
#include "GameObject.h"
#include "SpriteSheetLoader.h"

#include <iostream>
#include <fstream>

Animation::Animation(GameObject* parent, std::string name, float totalTime, float xPos, float yPos, bool shouldLockAtEnd)
{
	m_parent = parent;

	m_spriteBaseName = name;
	m_sheetName = m_spriteBaseName.substr(0, m_spriteBaseName.find_first_of("_"));

	//Load all sprites into the vector
	std::ifstream in("assets/Sprites/" + m_sheetName + "_anim.txt");

	m_sprites.clear();
	if(m_sheetName == "GoblinBomb")
	{
		std::cout << "Test1\n";
	}

	if(m_spriteBaseName == "GoblinBomb_falling_0")
	{
		std::cout << "Test2\n";
	}

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
			}
		}
	}

	m_currentSprite = m_sprites[0];

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

void Animation::play()
{
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
	if(m_shouldLockAtEnd && m_currentFrame == m_totalFrames - 1)
	{
	}

	else if(m_clock.getElapsedTime().asSeconds() > m_frameTime)
	{
		float m_totalDeltaTime = m_clock.getElapsedTime().asSeconds();

		while(m_totalDeltaTime > m_frameTime)
		{
			if(m_currentFrame == m_totalFrames - 1)
			{
				m_currentFrame = 0;
			}
			else{m_currentFrame++;}

			m_totalDeltaTime -= m_frameTime;
		}

		m_currentSprite = m_sprites[m_currentFrame];
		m_clock.restart();
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