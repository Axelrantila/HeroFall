#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "ComboManager.h"
#include <map>
#include <SFML/Window.hpp>

typedef std::pair<std::string, sf::Keyboard::Key> stringKeyPair;
typedef std::pair<std::string, bool> stringBoolPair;

struct ComboKeyInfo
{
	float timeRegistered;
	sf::Keyboard::Key key;
};

class InputManager
{
public:
	static InputManager* getInstance();

	void keyPressed(sf::Keyboard::Key key);
	void keyReleased(sf::Keyboard::Key key);

	bool isKeyDown(sf::Keyboard::Key key);
	bool isKeyDown(std::string function);

	bool isKeyPressed(sf::Keyboard::Key key);
	bool isKeyPressed(std::string function);

	bool d_testCombo();

	void update();
private:
	InputManager();
	~InputManager();

	std::map<std::string, sf::Keyboard::Key> m_keyFunctions;
	std::map<std::string, bool> m_keysDown;
	std::map<std::string, bool> m_keysPressed;
	std::map<std::string, bool> m_keysPressable;

	//FOR COMBOS
	sf::Clock m_comboClock;
	float m_comboTimeLimit;
	std::vector<ComboKeyInfo> m_comboKeys;
};

#endif