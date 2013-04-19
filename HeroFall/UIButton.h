#ifndef UIBUTTON_H
#define UIBUTTON_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class UIButton
{
public:
	    UIButton(sf::RenderWindow* window);
		~UIButton(void);
		virtual void Update(sf::Time deltaTime);
		virtual void Draw(sf::RenderWindow* window);
		virtual void SetPosition(sf::Vector2f);
		virtual void Move(sf::Vector2f);
		virtual void Center(sf::Vector2f);
		virtual bool Pressed(){ return bPressed; };
		//virtual void Scale(sf::Vector2f);
		//virtual void Opacity(int);

		enum BUTTON_STATE
		{
			STANDARD,
			SELECTED,
			DOWN
		} CURRENT_STATE;

		sf::Sprite* m_standard;
		sf::Sprite* m_selected;
		sf::Sprite* m_down;

protected:
		sf::RenderWindow* m_window;
		bool bPressed;
};

#endif

