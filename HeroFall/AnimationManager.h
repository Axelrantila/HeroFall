/*
ANIMATIONMANAGER

Funktion: Hantera animationer och �verg�ngar mellan de f�r olika karakt�rer

Vad som beh�vs:
*En std::map som inneh�ller alla animationer
*Parameter i konstruktorn f�r att s�tta defaultanimation
*Funktion som s�tter vilken animation som ska spelas upp n�r den nuvarande animationen har spelat klart sin loop
*Metod som stoppar den nuvarande animationen n�r den �r klar

Hur klassen ska anv�ndas:
*N�r man g�r n�gonting som ska spela upp en animation s� ska en metod anropas
*Vector med namn p� alla animationer som ska ing�
*Ska finnas en instans av detta f�r varje instans av ett objekt som ska spela upp animationer
*Animationer skall l�sas in MHA funktionerna i klassen Animation
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