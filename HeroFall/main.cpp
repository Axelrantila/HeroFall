#include "StateManager.h"

#include <iostream>

int main()
{
	std::cout << "Starting\n";

	StateManager* stateManager = new StateManager();
	stateManager->run();
	delete stateManager;

    return 0;
}