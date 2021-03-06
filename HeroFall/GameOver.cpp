#include "GameOver.h"
#include "SpriteSheetLoader.h"
#include "InputManager.h"
#include "ScoreManager.h"
#include "Util.h"

GameOver::GameOver(void)
{
	tracker = 0;
	backgroundGA = SpriteSheetLoader::getInstance()->getSprite ("GameOverScreenBG", "GameOverScreenBG");

	Continue = new UIButton();
	Continue->m_standard = SpriteSheetLoader::getInstance()->getSprite ("GameOverScreen", "Continue");
	Continue->m_selected = SpriteSheetLoader::getInstance()->getSprite ("GameOverScreen", "Continue_lit");
	Continue->m_down = SpriteSheetLoader::getInstance()->getSprite ("GameOverScreen", "Continue");
	Continue->Center(sf::Vector2f(1980, 1020));
	Continue->Move(sf::Vector2f(0.0f, (float)Continue->m_standard->getTextureRect().height + 150));

	Quit = new UIButton();
	Quit->m_standard = SpriteSheetLoader::getInstance()->getSprite ("GameOverScreen", "Main_Menu");
	Quit->m_selected = SpriteSheetLoader::getInstance()->getSprite ("GameOverScreen", "Main_Menu_lit");
	Quit->m_down = SpriteSheetLoader::getInstance()->getSprite ("GameOverScreen", "Main_Menu");
	Quit->SetPosition(sf::Vector2f(Continue->m_standard->getPosition()));
	Quit->Move(sf::Vector2f(0.0f, (float)Quit->m_standard->getTextureRect().height + 50));

	m_font = new sf::Font();
	m_font->loadFromFile("assets/Fonts/RomanUncialModern.ttf");
	m_text = new sf::Text();
	m_text->setFont(*m_font);
	m_text->setString("Final Score: " + Util::getInstance()->toString(ScoreManager::getInstance()->getScore()));
	m_text->setCharacterSize(120);
	m_text->setPosition(430.0f, 530.0f);
}


GameOver::~GameOver(void)
{
	delete m_text;
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
	window->draw(*backgroundGA);
	Continue->Draw(window);
	Quit->Draw(window);
	window->draw(*m_text);
}

void GameOver::handleEvents(sf::Event windowEvent)
{
}
