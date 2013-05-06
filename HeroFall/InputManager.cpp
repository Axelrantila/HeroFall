#include "InputManager.h"

InputManager::InputManager()
{
	m_keyFunctions.insert(stringKeyPair("P1_MOVE_UP", sf::Keyboard::W));
	m_keyFunctions.insert(stringKeyPair("P1_MOVE_LEFT", sf::Keyboard::A));
	m_keyFunctions.insert(stringKeyPair("P1_MOVE_DOWN", sf::Keyboard::S));
	m_keyFunctions.insert(stringKeyPair("P1_MOVE_RIGHT", sf::Keyboard::D));
	m_keyFunctions.insert(stringKeyPair("P1_BLOCK", sf::Keyboard::H));
	m_keyFunctions.insert(stringKeyPair("P1_ATTACK_1", sf::Keyboard::J));
	m_keyFunctions.insert(stringKeyPair("P1_ATTACK_2", sf::Keyboard::K));

	m_keysDown.insert(stringBoolPair("P1_MOVE_UP", false));
	m_keysDown.insert(stringBoolPair("P1_MOVE_LEFT", false));
	m_keysDown.insert(stringBoolPair("P1_MOVE_DOWN", false));
	m_keysDown.insert(stringBoolPair("P1_MOVE_RIGHT", false));
	m_keysDown.insert(stringBoolPair("P1_BLOCK", false));
	m_keysDown.insert(stringBoolPair("P1_ATTACK_1", false));
	m_keysDown.insert(stringBoolPair("P1_ATTACK_2", false));

	m_keysPressed.insert(stringBoolPair("P1_MOVE_UP", false));
	m_keysPressed.insert(stringBoolPair("P1_MOVE_LEFT", false));
	m_keysPressed.insert(stringBoolPair("P1_MOVE_DOWN", false));
	m_keysPressed.insert(stringBoolPair("P1_MOVE_RIGHT", false));
	m_keysPressed.insert(stringBoolPair("P1_BLOCK", false));
	m_keysPressed.insert(stringBoolPair("P1_ATTACK_1", false));
	m_keysPressed.insert(stringBoolPair("P1_ATTACK_2", false));

	m_keysPressable.insert(stringBoolPair("P1_MOVE_UP", true));
	m_keysPressable.insert(stringBoolPair("P1_MOVE_LEFT", true));
	m_keysPressable.insert(stringBoolPair("P1_MOVE_DOWN", true));
	m_keysPressable.insert(stringBoolPair("P1_MOVE_RIGHT", true));
	m_keysPressable.insert(stringBoolPair("P1_BLOCK", true));
	m_keysPressable.insert(stringBoolPair("P1_ATTACK_1", true));
	m_keysPressable.insert(stringBoolPair("P1_ATTACK_2", true));

	m_comboTimeLimit = 1.0f;
	m_comboClock.restart();
}

InputManager::~InputManager()
{
}

InputManager* InputManager::getInstance()
{
	static InputManager instance;
	return &instance;

}

void InputManager::update()
{
	for(std::map<std::string, bool>::iterator it = m_keysPressed.begin();
		it != m_keysPressed.end(); ++it)
	{
		it->second = false;
	}

	for(unsigned int a = 0; a < m_comboKeys.size();)
	{
		if(m_comboKeys[a].timeRegistered + m_comboTimeLimit <
			m_comboClock.getElapsedTime().asSeconds())
		{
			m_comboKeys.erase(m_comboKeys.begin() + a);
		}
		else
		{a++;}
	}
}

void InputManager::keyPressed(sf::Keyboard::Key key)
{
	for(std::map<std::string, sf::Keyboard::Key>::iterator it = m_keyFunctions.begin();
		it != m_keyFunctions.end();
		++it)
	{
		if(it->second == key)
		{
			m_keysDown[it->first] = true;
			m_keysPressed[it->first] = true;

			ComboKeyInfo tempComboKeyInfo;
			tempComboKeyInfo.key = key;
			tempComboKeyInfo.timeRegistered = m_comboClock.getElapsedTime().asSeconds();
			m_comboKeys.push_back(tempComboKeyInfo);
		}
	}
}

void InputManager::keyReleased(sf::Keyboard::Key key)
{
	for(std::map<std::string, sf::Keyboard::Key>::iterator it = m_keyFunctions.begin();
		it != m_keyFunctions.end(); ++it)
	{
		if(it->second == key)
		{
			m_keysDown[it->first] = false;
			m_keysPressed[it->first] = false;
			m_keysPressable[it->first] = true;
		}
	}
}

bool InputManager::isKeyDown(sf::Keyboard::Key key)
{
	for(std::map<std::string, sf::Keyboard::Key>::iterator it = m_keyFunctions.begin();
		it != m_keyFunctions.end();
		++it)
	{
		if(it->second == key)
		{
			return m_keysDown[it->first];
		}
	}

	return false;
}

bool InputManager::isKeyDown(std::string function)
{
	for(std::map<std::string, sf::Keyboard::Key>::iterator it = m_keyFunctions.begin();
		it != m_keyFunctions.end(); ++it)
	{
		if(it->first == function)
		{
			return m_keysDown[it->first];
		}
	}

	return false;
}

bool InputManager::isKeyPressed(sf::Keyboard::Key key)
{
	for(std::map<std::string, sf::Keyboard::Key>::iterator it = m_keyFunctions.begin();
		it != m_keyFunctions.end();
		++it)
	{
		if(it->second == key && m_keysPressable[it->first] && m_keysPressed[it->first])
		{
			m_keysPressable[it->first] = false;
			return m_keysPressed[it->first];
		}
	}

	return false;
}

bool InputManager::isKeyPressed(std::string function)
{
	for(std::map<std::string, sf::Keyboard::Key>::iterator it = m_keyFunctions.begin();
		it != m_keyFunctions.end(); ++it)
	{
		if(it->first == function && m_keysPressable[it->first] && m_keysPressed[it->first])
		{
			m_keysPressable[it->first] = false;
			return m_keysPressed[it->first];
		}
	}

	return false;
}

bool InputManager::d_testCombo()
{
	if(m_comboKeys.size() >= 2)
	{
		if(m_comboKeys[0].key == m_keyFunctions["P1_ATTACK_1"]
		&& m_comboKeys[1].key == m_keyFunctions["P1_ATTACK_2"])
		{
			m_comboKeys.pop_back();
			m_comboKeys.pop_back();
			return true;
		}
	}

	return false;
}