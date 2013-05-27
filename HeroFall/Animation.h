#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>

#include "Character.h"
#include "CharacterDirection.h"

class Animation
{
public:
	Animation(Character* parent, std::string name, float totalTime, float xPos, float yPos, bool shouldLockAtEnd = false);
	~Animation();

	void play(CharacterDirection direction = DIR_NONE);
	void pause();
	void stop();

	void update(float xPos, float yPos);

	sf::Sprite* getCurrentSprite();
	sf::Sprite* getSprite(unsigned int index);
	unsigned int getCurrentFrame();
	unsigned int getMaxFrameNr(){return m_totalFrames-1;}

	std::string getName() {return m_spriteBaseName;}

private:
	Character* m_parent;
	CharacterDirection m_standardDirection;

	bool m_mirrored;
	sf::Vector2f m_mirroredOffsetPosition;
	std::map<sf::Sprite*, bool> m_mirroredImages;

	std::string m_sheetName;
	std::string m_spriteBaseName;
	
	bool m_playing;
	bool m_stopped;

	float m_frameTime;
	float m_totalTime;
	unsigned int m_currentFrame;
	unsigned int m_totalFrames;
	bool m_shouldLockAtEnd;

	sf::Sprite* m_currentSprite;
	std::vector<sf::Sprite*> m_sprites;

	sf::Clock m_clock;
	float m_xPos;
	float m_yPos;

	bool m_wasStarted;
};

#endif