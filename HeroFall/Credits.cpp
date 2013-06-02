#include "Credits.h"
#include "InputManager.h"

Credits::Credits()
{
}


Credits::~Credits()
{
}

void Credits::update(StateManager* stateManager, float deltaTime)
{
	if(InputManager::getInstance()->isKeyPressed("P1_BLOCK"))
	{
		this->markForDeletion();
		stateManager->addState(STATE_MENUS);
	}
}

void Credits::draw(sf::RenderWindow* window)
{
}