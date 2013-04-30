#include "AnimationManager.h"
#include "GameObject.h"

AnimationManager::AnimationManager(GameObject* parent)
{
	m_parent = parent;
	m_currentAnimation = nullptr;
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::addAnimation(std::string name, float totalTime, float xPos, float yPos)
{
	m_animations.insert(std::pair<std::string, Animation*>(name, new Animation(m_parent, name, totalTime, xPos, yPos)));
}

void AnimationManager::setCurrentAnimation(std::string name)
{
	for(std::map<std::string, Animation*>::iterator it = m_animations.begin();
		it != m_animations.end(); ++it)
	{
		if(it->second->getName() == name)
		{
			if(m_currentAnimation != nullptr)
			{m_currentAnimation->stop();}

			m_currentAnimation = it->second;
			m_currentAnimation->play();
		}
	}
}

sf::Sprite* AnimationManager::getCurrentSprite()
{
	if(m_currentAnimation != nullptr)
	{
		return m_currentAnimation->getCurrentSprite();
	}
	else
	{
		return nullptr;
	}
}

void AnimationManager::update(float xPos, float yPos)
{
	for(std::map<std::string, Animation*>::iterator it = m_animations.begin();
		it != m_animations.end(); ++it)
	{
		it->second->update(xPos, yPos);
	}
}

Animation* AnimationManager::getAnimation(std::string name)
{
	for(std::map<std::string, Animation*>::iterator it = m_animations.begin(); it != m_animations.end(); ++it)
	{
		if(it->first == name)
		{
			return it->second;
		}
	}

	return nullptr;
}

bool AnimationManager::isCurrentAnimation(std::string name)
{
	for(std::map<std::string, Animation*>::iterator it = m_animations.begin(); it != m_animations.end(); ++it)
	{
		if(it->first == name
			&& it->second == m_currentAnimation)
		{
			return true;
		}
	}

	return false;
}