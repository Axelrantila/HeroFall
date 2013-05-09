#include "HUD.h"
#include "SpriteSheetLoader.h"


HUD::HUD(sf::View* view, Player* player)
	:GameObject(PT_UPPER_LEFT,
	view->getCenter().x - view->getSize().x/2.0f,
	view->getCenter().y - view->getSize().y/2.0f)
{
	m_GUI = SpriteSheetLoader::getInstance()->getSprite("GUI", "GUI_0");
	m_healthbar = SpriteSheetLoader::getInstance()->getSprite("Healthbar", "Healthbar_0");
	m_healthbar->setOrigin(10.0f, 20.0f);
	m_view = view;
	m_player = player;

	m_playerMaxHealth = player->getHealth();
}


HUD::~HUD(void)
{
}

void HUD::update()
{
	m_GUI->setPosition(m_view->getCenter().x - m_view->getSize().x/2.0f
		,m_view->getCenter().y - m_view->getSize().y/2.0f);
	m_healthbar->setScale(m_player->getHealth() / m_playerMaxHealth, 1.0f);
	m_healthbar->setPosition(m_GUI->getPosition().x + 225.0f, m_GUI->getPosition().y + 110.0f);
}

void HUD::draw(sf::RenderWindow* window)
{
	window->draw(*m_GUI);
	window->draw(*m_healthbar);
}