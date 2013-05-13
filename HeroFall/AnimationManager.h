#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "Animation.h"

#include <map>

class AnimationManager
{
public:
	AnimationManager(GameObject* parent);
	~AnimationManager();

	void addAnimation(std::string name, float totalTime, float xPos, float yPos, bool shouldLockAtEnd = false);
	void setCurrentAnimation(std::string name);
	void update(float xPos, float yPos);

	sf::Sprite* getCurrentSprite();
	Animation* getCurrentAnimation(){return m_currentAnimation;}
	Animation* getAnimation(std::string name);
	bool isCurrentAnimation(std::string name);

private:
	GameObject* m_parent;

	std::map<std::string, Animation*> m_animations;
	Animation* m_currentAnimation;
};

#endif