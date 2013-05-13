#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML\Graphics.hpp>
#include <string>
#include <vector>

class GameObject;

class Animation
{
public:
	Animation(GameObject* parent, std::string name, float totalTime, float xPos, float yPos, bool shouldLockAtEnd = false);
	~Animation();

	void play();
	void pause();
	void stop();

	void update(float xPos, float yPos);

	sf::Sprite* getCurrentSprite();
	sf::Sprite* getSprite(unsigned int index);
	unsigned int getCurrentFrame();

	std::string getName() {return m_spriteBaseName;}

private:
	GameObject* m_parent;
	std::string m_sheetName;
	std::string m_spriteBaseName;
	
	bool m_playing;
	bool m_stopped;

	float m_frameTime;
	unsigned int m_currentFrame;
	unsigned int m_totalFrames;
	bool m_shouldLockAtEnd;

	sf::Sprite* m_currentSprite;
	std::vector<sf::Sprite*> m_sprites;

	sf::Clock m_clock;

	float m_xPos;
	float m_yPos;
};

#endif