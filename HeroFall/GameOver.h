#include "State.h"
#include "StateManager.h"
#include "UIButton.h"

class GameOver
	:public State
{
public:
	GameOver();
	~GameOver(void);

	void update(StateManager* stateManager, float delta);
	void draw(sf::RenderWindow* window);
	void handleEvents(sf::Event windowEvent);

private:
	UIButton* Continue;
	UIButton* Quit;
	sf::Sprite* backgroundGA;
	int tracker;
};

