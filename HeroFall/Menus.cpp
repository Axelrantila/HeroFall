#include "Menus.h"
#include "InputManager.h"
#include "StateManager.h"

Menus::Menus()
{
	tracker = 0;
	currentState = MAIN;
	background = SpriteSheetLoader::getInstance()->getSprite ("MainMenuBG", "MainMenuBG_0");

	Play = new UIButton();
	Play->m_standard = SpriteSheetLoader::getInstance()->getSprite ("MainMenuButtons", "MainMenuButtons_Play");
	Play->m_selected = SpriteSheetLoader::getInstance()->getSprite ("MainMenuButtons", "MainMenuButtons_Play_lit");
	Play->m_down = SpriteSheetLoader::getInstance()->getSprite ("MainMenuButtons", "MainMenuButtons_Play");
	Play->Center(sf::Vector2f(1920, 1080));
	Play->Move(sf::Vector2f(0.0f, -(float)Play->m_standard->getTextureRect().height - 50));

	Options = new UIButton();
	Options->m_standard = SpriteSheetLoader::getInstance()->getSprite ("MainMenuButtons", "MainMenuButtons_Options");
	Options->m_selected = SpriteSheetLoader::getInstance()->getSprite ("MainMenuButtons", "MainMenuButtons_Options_lit");
	Options->m_down = SpriteSheetLoader::getInstance()->getSprite ("MainMenuButtons", "MainMenuButtons_Options");
	Options->Center(sf::Vector2f(1920, 1080));

	Credits = new UIButton();
	Credits->m_standard = SpriteSheetLoader::getInstance()->getSprite ("MainMenuButtons", "MainMenuButtons_Credits");
	Credits->m_selected = SpriteSheetLoader::getInstance()->getSprite ("MainMenuButtons", "MainMenuButtons_Credits_lit");
	Credits->m_down = SpriteSheetLoader::getInstance()->getSprite ("MainMenuButtons", "MainMenuButtons_Credits");
	Credits->SetPosition(sf::Vector2f(Options->m_standard->getPosition()));
	Credits->Move(sf::Vector2f(0.0f, (float)Credits->m_standard->getTextureRect().height + 50));

	Quit = new UIButton();
	Quit->m_standard = SpriteSheetLoader::getInstance()->getSprite ("MainMenuButtons", "MainMenuButtons_Exit");
	Quit->m_selected = SpriteSheetLoader::getInstance()->getSprite ("MainMenuButtons", "MainMenuButtons_Exit_lit");
	Quit->m_down = SpriteSheetLoader::getInstance()->getSprite ("MainMenuButtons", "MainMenuButtons_Exit");
	Quit->SetPosition(sf::Vector2f(Credits->m_standard->getPosition()));
	Quit->Move(sf::Vector2f(0.0f, (float)Quit->m_standard->getTextureRect().height + 50));
}

void Menus::update(StateManager* stateManager, float delta)
{
	if ( tracker == 3 && InputManager::getInstance()->isKeyPressed("P1_MOVE_DOWN") )
	{
		tracker = 0;
	}
	else if ( InputManager::getInstance()->isKeyPressed("P1_MOVE_DOWN") )
	{
		tracker ++;
	}
	if ( tracker == 0 && InputManager::getInstance()->isKeyPressed("P1_MOVE_UP" ))
	{
		tracker = 3;
	}
	else if ( InputManager::getInstance()->isKeyPressed("P1_MOVE_UP") )
	{
		tracker --;
	}

	if (currentState == MAIN)
	{
		Play->Update(delta);
		if ( Play->Pressed() )
		{
			markForDeletion();
			stateManager->addState(STATE_GAME);
		}
		Options->Update(delta);
		if ( Options->Pressed() )
			{ currentState = OPTIONS; }
		Credits->Update(delta);
		if ( Credits->Pressed() )
			{ currentState = CREDITS; }
		Quit->Update(delta);
		if ( Quit->Pressed() )
		{
				markForDeletion();
		}
	}

	////////////////////////////////////////////////////////
	if (tracker == 0)
	{ 
		Play->CURRENT_STATE = SELECTED;
		Options->CURRENT_STATE = STANDARD;
		Credits->CURRENT_STATE = STANDARD;
		Quit->CURRENT_STATE = STANDARD;
	}
	else if (tracker == 1)
	{ 
		Play->CURRENT_STATE = STANDARD;
		Options->CURRENT_STATE = SELECTED;
		Credits->CURRENT_STATE = STANDARD;
		Quit->CURRENT_STATE = STANDARD;
	}
	else if (tracker == 2)
	{ 
		Play->CURRENT_STATE = STANDARD;
		Options->CURRENT_STATE = STANDARD;
		Credits->CURRENT_STATE = SELECTED;
		Quit->CURRENT_STATE = STANDARD;
	}
	else if (tracker == 3)
	{ 
		Play->CURRENT_STATE = STANDARD;
		Options->CURRENT_STATE = STANDARD;
		Credits->CURRENT_STATE = STANDARD;
		Quit->CURRENT_STATE = SELECTED;
	}
}

void Menus::draw(sf::RenderWindow* window)
{
	window->draw(*background);

	Play->Draw(window);
	Options->Draw(window);
	Credits->Draw(window);
	Quit->Draw(window);
}

Menus::~Menus(void)
{
	delete Play;
	delete Options;
	delete Credits;
	delete Quit;
	delete background;
}

void Menus::handleEvents(sf::Event windowEvent)
{
}
