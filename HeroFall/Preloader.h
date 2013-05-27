#ifndef PRELOADER_H
#define PRELOADER_H

#include "State.h"

#include <vector>

class Animation;
/*
Vad som skall göras

Läsa in trollets och avatarens animationer

"Spela upp" en per frame i kod

Rita ut animationen

Rita ut loadingscreenen
*/

class Preloader
	:public State
{
public:
	Preloader();
	~Preloader();

	void update(StateManager* stateManager, float deltaTime);
	void draw(sf::RenderWindow* window);
	void handleEvents(sf::Event windowEvent){}; //Not used

/*private:
	std::vector<Animation*>*/
};

#endif