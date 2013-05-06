#include "GameOver.h"
#include "SpriteSheetLoader.h"
#include "InputManager.h"

GameOver::GameOver(void)
{
	tracker = 0;
	//backgroundGA = SpriteSheetLoader::getInstance()->getSprite ("DBG", "DBG_0");

	Continue = new UIButton();
	Continue->m_standard = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_Audio");
	Continue->m_selected = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_AudioSelected");
	Continue->m_down = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_AudioSelected");
	Continue->Center(sf::Vector2f(800, 800));
	Continue->Move(sf::Vector2f(0.0f, (float)Continue->m_standard->getTextureRect().height + 50));

	Quit = new UIButton();
	Quit->m_standard = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_Video");
	Quit->m_selected = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_VideoSelected");
	Quit->m_down = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_VideoSelected");
	Quit->SetPosition(sf::Vector2f(Continue->m_standard->getPosition()));
	Quit->Move(sf::Vector2f(0.0f, (float)Quit->m_standard->getTextureRect().height + 50));
}


GameOver::~GameOver(void)
{
}

void GameOver::update(StateManager* stateManager, float delta)
{
	if ( tracker == 1 && InputManager::getInstance()->isKeyPressed("P1_MOVE_DOWN") )
	{
		tracker = 0;
	}
	else if ( InputManager::getInstance()->isKeyPressed("P1_MOVE_DOWN") )
	{
		tracker ++;
	}
	if ( tracker == 0 && InputManager::getInstance()->isKeyPressed("P1_MOVE_UP" ))
	{
		tracker = 1;
	}
	else if ( InputManager::getInstance()->isKeyPressed("P1_MOVE_UP") )
	{
		tracker --;
	}

	if (tracker == 0)
	{
		Continue->CURRENT_STATE = SELECTED;
		Quit->CURRENT_STATE = STANDARD;
	}
	if (tracker == 1)
	{
		Continue->CURRENT_STATE = STANDARD;
		Quit->CURRENT_STATE = SELECTED;
	}

	Continue->Update(delta);
		if ( Continue->Pressed() )
		{ 
			markForDeletion();
			stateManager->addState (STATE_GAME);
		}
	Quit->Update(delta);
		if ( Quit->Pressed() )
		{
			markForDeletion();
			stateManager->addState (STATE_MENUS);
		}
}

void GameOver::draw(sf::RenderWindow* window)
{
	//window->draw(*backgroundGA);
	Continue->Draw(window);
	Quit->Draw(window);
}

void GameOver::handleEvents(sf::Event windowEvent)
{
}
