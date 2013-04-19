/*
ANIMATIONMANAGER

Funktion: Hantera animationer och övergångar mellan de för olika karaktärer

Vad som behövs:
*En std::map som innehåller alla animationer
*Parameter i konstruktorn för att sätta defaultanimation
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
	AnimationManager();
	~AnimationManager();

	std::map<std::string, Animation*> m_animations;
};

#endif