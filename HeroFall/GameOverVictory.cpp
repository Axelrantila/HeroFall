#include "GameOverVictory.h"
#include "InputManager.h"
#include "ScoreManager.h"
#include "SettingsManager.h"
#include "SpriteSheetLoader.h"
#include "StateManager.h"
#include "Util.h"

#include <SFML\Graphics.hpp>

#include <iostream>

GameOverVictory::GameOverVictory()
{
	m_bg = SpriteSheetLoader::getInstance()->getSprite("Highscore", "Highscore_BG");

	m_letters[0] = 'A';
	m_letters[1] = 'A';
	m_letters[2] = 'A';

	m_currentLetter = 0;
	
	m_font = new sf::Font();
	m_font->loadFromFile("assets/Fonts/Dragv2.ttf");

	m_score1Text = new sf::Text();
	m_score1Text->setFont(*m_font);
	m_score1Text->setPosition(655.0f, 230.0f);
	m_score1Text->setCharacterSize(120);

	m_score2Text = new sf::Text();
	m_score2Text->setFont(*m_font);
	m_score2Text->setPosition(655.0f, 530.0f);
	m_score2Text->setCharacterSize(120);

	m_score3Text = new sf::Text();
	m_score3Text->setFont(*m_font);
	m_score3Text->setPosition(655.0f, 830.0f);
	m_score3Text->setCharacterSize(120);

	if(ScoreManager::getInstance()->getScore() > SettingsManager::getSettings()->HIGHSCORE_SCORE)
	{
		m_scoreToBeUpdated = 0;
		m_score1Text->setString(m_letters);
		m_score2Text->setString(SettingsManager::getSettings()->HIGHSCORE2_NAME + "\t" + Util::getInstance()->toString(SettingsManager::getSettings()->HIGHSCORE2_SCORE));
		m_score3Text->setString(SettingsManager::getSettings()->HIGHSCORE3_NAME + "\t" + Util::getInstance()->toString(SettingsManager::getSettings()->HIGHSCORE3_SCORE));
		m_renderText = m_score1Text;
	}
	else if(ScoreManager::getInstance()->getScore() > SettingsManager::getSettings()->HIGHSCORE2_SCORE)
	{
		m_scoreToBeUpdated = 1;
		m_score1Text->setString(SettingsManager::getSettings()->HIGHSCORE_NAME + "\t" + Util::getInstance()->toString(SettingsManager::getSettings()->HIGHSCORE_SCORE));
		m_score2Text->setString(m_letters);
		m_score3Text->setString(SettingsManager::getSettings()->HIGHSCORE3_NAME + "\t" + Util::getInstance()->toString(SettingsManager::getSettings()->HIGHSCORE3_SCORE));
		m_renderText = m_score2Text;
	}
	else
	{
		m_scoreToBeUpdated = 2;
		m_score2Text->setString(SettingsManager::getSettings()->HIGHSCORE2_NAME + "\t" + Util::getInstance()->toString(SettingsManager::getSettings()->HIGHSCORE2_SCORE));
		m_score1Text->setString(SettingsManager::getSettings()->HIGHSCORE_NAME + "\t" + Util::getInstance()->toString(SettingsManager::getSettings()->HIGHSCORE_SCORE));
		m_score3Text->setString(m_letters);
		m_renderText = m_score3Text;
	}
}


GameOverVictory::~GameOverVictory()
{
	delete m_font;
}

void GameOverVictory::update(StateManager* stateManager, float deltaTime)
{
	//If the player has finished putting in his/her letters
	if(InputManager::getInstance()->isKeyPressed("P1_BLOCK"))
	{
		if(m_scoreToBeUpdated == 0)
		{
			SettingsManager::getSettings()->HIGHSCORE3_SCORE = SettingsManager::getSettings()->HIGHSCORE2_SCORE;
			SettingsManager::getSettings()->HIGHSCORE3_NAME = SettingsManager::getSettings()->HIGHSCORE2_NAME;

			SettingsManager::getSettings()->HIGHSCORE2_SCORE = SettingsManager::getSettings()->HIGHSCORE_SCORE;
			SettingsManager::getSettings()->HIGHSCORE2_NAME = SettingsManager::getSettings()->HIGHSCORE_NAME;

			SettingsManager::getSettings()->HIGHSCORE_SCORE = ScoreManager::getInstance()->getScore();
			SettingsManager::getSettings()->HIGHSCORE_NAME = m_letters;
		}
		else if(m_scoreToBeUpdated == 1)
		{
			SettingsManager::getSettings()->HIGHSCORE3_SCORE = SettingsManager::getSettings()->HIGHSCORE2_SCORE;
			SettingsManager::getSettings()->HIGHSCORE3_NAME = SettingsManager::getSettings()->HIGHSCORE2_NAME;

			SettingsManager::getSettings()->HIGHSCORE2_SCORE = ScoreManager::getInstance()->getScore();
			SettingsManager::getSettings()->HIGHSCORE2_NAME = m_letters;
		}
		else
		{
			SettingsManager::getSettings()->HIGHSCORE3_SCORE = ScoreManager::getInstance()->getScore();
			SettingsManager::getSettings()->HIGHSCORE3_NAME = m_letters;
		}
		
		SettingsManager::getInstance()->saveSettings();
		this->markForDeletion();
		stateManager->addState(STATE_GAME);
	}

	//Check if letter is being changed
	if(InputManager::getInstance()->isKeyPressed("P1_MOVE_LEFT"))
	{
		m_currentLetter--;
		if(m_currentLetter < 0)
		{m_currentLetter = 2;}
	}

	else if(InputManager::getInstance()->isKeyPressed("P1_MOVE_RIGHT"))
	{
		m_currentLetter++;
		if(m_currentLetter > 2)
		{m_currentLetter = 0;}
	}

	//Change the current letter
	else if(InputManager::getInstance()->isKeyPressed("P1_MOVE_DOWN"))
	{
		m_letters[m_currentLetter]++;
		if(m_letters[m_currentLetter] > 'Z')
		{m_letters[m_currentLetter] = 'A';}
	}

	else if(InputManager::getInstance()->isKeyPressed("P1_MOVE_UP"))
	{
		m_letters[m_currentLetter]--;
		if(m_letters[m_currentLetter] < 'A')
		{m_letters[m_currentLetter] = 'Z';}
	}

	

	std::string newString = m_letters;
	newString.append("\t");
	newString.append(Util::getInstance()->toString(ScoreManager::getInstance()->getScore()));

	std::cout << m_letters <<  "\t" << newString << std::endl;

	m_renderText->setString(newString);
}

void GameOverVictory::draw(sf::RenderWindow* window)
{
	window->draw(*m_bg);
	window->draw(*m_score1Text);
	window->draw(*m_score2Text);
	window->draw(*m_score3Text);
}

void GameOverVictory::handleEvents(sf::Event windowEvent)
{
}