#include "StateManager.h"

#include <iostream>

int main()
{
	StateManager* stateManager = new StateManager();
	stateManager->run();
	delete stateManager;

    return 0;
}