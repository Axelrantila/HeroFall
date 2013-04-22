#include "UIButton.h"
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

UIButton::UIButton()
{
	bPressed = false;
	m_standard = nullptr;
	m_selected = nullptr;
	m_down = nullptr;
}


UIButton::~UIButton(void)
{
	if(m_standard != nullptr)
		delete m_standard;
	if(m_selected != nullptr)
		delete m_selected;
	if(m_down != nullptr)
		delete m_down;
}

void UIButton::Update( float delta )
{
	bPressed = false;
	if (CURRENT_STATE == SELECTED /*&& sf::Keyboard::isKeyPressed(sf::Keyboard::Return)*/)
	{ bPressed = true; }
}

void UIButton::Draw( sf::RenderWindow* window )
{
	switch(CURRENT_STATE)
	{
		case SELECTED:
			{
				window->draw(*m_selected);
				break;
			}
		case DOWN:
			{
				window->draw(*m_down);
				break;
			}
		default:
		case STANDARD:
			{
				window->draw(*m_standard);
				break;
			}
	}
}

void UIButton::SetPosition( sf::Vector2f newPos )
{
	m_standard->setPosition(newPos);
	m_selected->setPosition(newPos);
	m_down->setPosition(newPos);
}

void UIButton::Move( sf::Vector2f newPos )
{
	m_standard->move(newPos);
	m_selected->move(newPos);
	m_down->move(newPos);
}

void UIButton::Center( sf::Vector2f ref )
{
	m_standard->setPosition( ref.x/2.0f - (float)m_standard->getTextureRect().width/2.0f, ref.y/2.0f - (float)m_standard->getTextureRect().height/2.0f );
	m_selected->setPosition( ref.x/2.0f - (float)m_standard->getTextureRect().width/2.0f, ref.y/2.0f - (float)m_standard->getTextureRect().height/2.0f );
	m_down->setPosition( ref.x/2.0f - (float)m_standard->getTextureRect().width/2.0f, ref.y/2.0f - (float)m_standard->getTextureRect().height/2.0f );
}

//void UIButton::Scale( sf::Vector2f NewScale )
//{
//	m_standard->setScale(NewScale);
//	m_hover->setScale(NewScale);
//	m_down->setScale(NewScale);
//	m_disabled->setScale(NewScale);
//}

//void UIButton::Opacity( int Alpha )
//{
//	sf::Color C = m_standard->getColor();
//	C.a = Alpha;
//	m_standard->setColor(C);
//	sf::Color C2 = m_hover->getColor();
//	C2.a = Alpha;
//	m_hover->setColor(C2);
//	sf::Color C3 = m_down->getColor();
//	C3.a = Alpha;
//	m_down->setColor(C3);
//	sf::Color C4 = m_disabled->getColor();
//	C4.a = Alpha;
//	m_disabled->setColor(C4);
//}
