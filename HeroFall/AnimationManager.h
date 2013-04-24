/*
ANIMATIONMANAGER

Funktion: Hantera animationer och övergångar mellan de för olika karaktärer

Vad som behövs:
*Funktion som sätter vilken animation som ska spelas upp när den nuvarande animationen har spelat klart sin loop
*Metod som stoppar den nuvarande animationen när den är klar

Hur klassen ska användas:
*När man gör någonting som ska spela upp en animation så ska en metod anropas
*Vector med namn på alla animationer som ska ingå
*Ska finnas en instans av detta för varje instans av ett objekt som ska spela upp animationer
*Animationer skall läsas in MHA funktionerna i klassen Animation
*/
#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "Animation.h"

#include <map>

class AnimationManager
{
public:
	AnimationManager(GameObject* parent);
	~AnimationManager();

	void addAnimation(std::string name, float totalTime, float xPos, float yPos);
	void setCurrentAnimation(std::string name);
	void update(float xPos, float yPos);

	sf::Sprite* getCurrentSprite();

private:
	GameObject* m_parent;

	std::map<std::string, Animation*> m_animations;
	Animation* m_currentAnimation;
};

#endif