#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "Animation.h"

#include <map>

class AnimationManager
{
public:
	AnimationManager(Character* parent);
	~AnimationManager();

	void addAnimation(std::string name, float totalTime, float xPos, float yPos, bool shouldLockAtEnd = false);
	void setCurrentAnimation(std::string name, CharacterDirection direction = DIR_NONE);
	void update(float xPos, float yPos);

	sf::Sprite* getCurrentSprite();
	Animation* getCurrentAnimation(){return m_currentAnimation;}
	Animation* getAnimation(std::string name);
	bool isCurrentAnimation(std::string name);

private:
	Character* m_parent;

	std::map<std::string, Animation*> m_animations;
	Animation* m_currentAnimation;

	CharacterDirection m_currentDirection;
};

#endif