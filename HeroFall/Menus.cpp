#include "Menus.h"
#include "InputManager.h"

Menus::Menus(sf::RenderWindow* window)
{
	tracker = 0;
	currentState = MAIN;
	background = SpriteSheetLoader::getInstance()->getSprite ("DBG", "DBG_0");

	Play = new UIButton(window);
	Play->m_standard = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_Audio");
	Play->m_selected = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_AudioSelected");
	Play->m_down = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_AudioSelected");
	Play->Center(sf::Vector2f(800, 800));
	Play->Move(sf::Vector2f(0, -Play->m_standard->getTextureRect().height + 50));

	Options = new UIButton(window);
	Options->m_standard = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_Controls");
	Options->m_selected = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_ControlsSelected");
	Options->m_down = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_ControlsSelected");
	Options->Center(sf::Vector2f(800, 800));

	Credits = new UIButton(window);
	Credits->m_standard = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_MainMenu");
	Credits->m_selected = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_MainMenuSelected");
	Credits->m_down = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_MainMenuSelected");
	Credits->SetPosition(sf::Vector2f(Options->m_standard->getPosition()));
	Credits->Move(sf::Vector2f(0, Credits->m_standard->getTextureRect().height + 50));

	Quit = new UIButton(window);
	Quit->m_standard = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_Video");
	Quit->m_selected = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_VideoSelected");
	Quit->m_down = SpriteSheetLoader::getInstance()->getSprite ("MenuButtons", "MenuButtons_VideoSelected");
	Quit->SetPosition(sf::Vector2f(Credits->m_standard->getPosition()));
	Quit->Move(sf::Vector2f(0, Quit->m_standard->getTextureRect().height + 50));
}

void Menus::Update(sf::Time deltaTime)
{
	if (tracker == 0)
	{ 
		Play->SELECTED;
		Options->STANDARD;
		Credits->STANDARD;
		Quit->STANDARD;
	}
	if (tracker == 1)
	{ 
		Play->STANDARD;
		Options->SELECTED;
		Credits->STANDARD;
		Quit->STANDARD;
	}
	if (tracker == 2)
	{ 
		Play->STANDARD;
		Options->STANDARD;
		Credits->SELECTED;
		Quit->STANDARD;
	}
	if (tracker == 3)
	{ 
		Play->STANDARD;
		Options->STANDARD;
		Credits->STANDARD;
		Quit->SELECTED;
	}
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
	{
		tracker ++;
	}
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
	{
		tracker --;
	}
	if ( tracker == 3 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
	{
		tracker = 0;
	}
	if ( tracker == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
	{
		tracker = 3;
	}
	if (currentState == MAIN)
	{
		Play->Update(deltaTime);
		if ( Play->Pressed() )
			{  }
		Options->Update(deltaTime);
		if ( Options->Pressed() )
			{ currentState = OPTIONS; }
		Credits->Update(deltaTime);
		if ( Credits->Pressed() )
			{ currentState = CREDITS; }
		Quit->Update(deltaTime);
		if ( Quit->Pressed() )
			{  }
	}
}

void Menus::Draw(sf::RenderWindow *window)
{
	window->draw(*background);

	if (currentState == MAIN)
	{
		Play->Draw(window);
		Options->Draw(window);
		Credits->Draw(window);
		Quit->Draw(window);
	}
}

Menus::~Menus(void)
{
	delete Play;
	delete Options;
	delete Credits;
	delete Quit;
}
