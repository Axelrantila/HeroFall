#include "ComboManager.h"
#include "HUD.h"
#include "ScoreManager.h"
#include "SpriteSheetLoader.h"
#include "Util.h"

HUD::HUD(sf::View* view, Player* player)
	:GameObject(PT_UPPER_LEFT,
	view->getCenter().x - view->getSize().x/2.0f,
	view->getCenter().y - view->getSize().y/2.0f)
{
	m_GUI = SpriteSheetLoader::getInstance()->getSprite("GUI", "GUI_0");
	m_healthbar = SpriteSheetLoader::getInstance()->getSprite("Healthbar", "Healthbar_0");
	m_healthbar->setOrigin(10.0f, 20.0f);
	m_combobar = SpriteSheetLoader::getInstance()->getSprite("ComboBar", "ComboBar_0");
	m_combobar->setOrigin(30.0f, 42.0f);

	m_view = view;
	m_player = player;

	m_playerMaxHealth = player->getHealth();

	m_font = new sf::Font();
	m_font->loadFromFile("assets/Fonts/VINERITC.TTF");

	m_text =  new sf::Text("0", *m_font, 50);
	m_text->setColor(sf::Color(255, 127, 0));
}


HUD::~HUD(void)
{
	delete m_font;
	delete m_text;
}

void HUD::update()
{
	m_GUI->setPosition(m_view->getCenter().x - m_view->getSize().x/2.0f
		,m_view->getCenter().y - m_view->getSize().y/2.0f);

	m_healthbar->setScale(m_player->getHealth() / m_playerMaxHealth, 1.0f);
	m_healthbar->setPosition(m_GUI->getPosition().x + 225.0f, m_GUI->getPosition().y + 110.0f);

	if(ComboManager::getInstance()->getComboPercentage() >= 1.0f)
	{
		m_combobar = SpriteSheetLoader::getInstance()->getSprite("ComboBar", "ComboBar_1");
		m_combobar->setOrigin(30.0f, 42.0f);
	}
	else
	{
		m_combobar = SpriteSheetLoader::getInstance()->getSprite("ComboBar", "ComboBar_0");
		m_combobar->setOrigin(30.0f, 42.0f);
	}

	m_combobar->setScale(Util::getInstance()->getCapedCalue(ComboManager::getInstance()->getComboPercentage(), 1.0f), 1.0f);
	m_combobar->setPosition(m_GUI->getPosition().x + 255.0f, m_GUI->getPosition().y + 180.0f);

	m_text->setPosition(m_GUI->getGlobalBounds().left + m_GUI->getGlobalBounds().width
		, m_GUI->getGlobalBounds().top);
}

void HUD::update(float delta)
{
	m_text->setString(Util::getInstance()->toString(ScoreManager::getInstance()->getScore())
		+ "\t" + Util::getInstance()->toString(1.0f/delta));
	update();
}

void HUD::draw(sf::RenderWindow* window)
{
	window->draw(*m_GUI);
	window->draw(*m_healthbar);
	window->draw(*m_combobar);
	window->draw(*m_text);
}