#ifndef UIBUTTON_H
#define UIBUTTON_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

enum BUTTON_STATE
		{
			STANDARD,
			SELECTED,
			DOWN
		}; 

class UIButton
{
public:
	    UIButton();
		~UIButton(void);
		virtual void Update(float delta);
		virtual void Draw(sf::RenderWindow* window);
		virtual void SetPosition(sf::Vector2f);
		virtual void Move(sf::Vector2f);
		virtual void Center(sf::Vector2f);
		virtual bool Pressed(){ return bPressed; };
		//virtual void Scale(sf::Vector2f);
		//virtual void Opacity(int);

		BUTTON_STATE CURRENT_STATE;

		sf::Sprite* m_standard;
		sf::Sprite* m_selected;
		sf::Sprite* m_down;

protected:
		bool bPressed;
};

#endif

