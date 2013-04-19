#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Window.hpp>

#include <map>

typedef std::pair<std::string, sf::Keyboard::Key> stringKeyPair;
typedef std::pair<std::string, bool> stringBoolPair;

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

	void update();
private:
	InputManager();
	~InputManager();

	std::map<std::string, sf::Keyboard::Key> m_keyFunctions;
	std::map<std::string, bool> m_keysDown;
	std::map<std::string, bool> m_keysPressed;
	std::map<std::string, bool> m_keysPressable;
};

#endif