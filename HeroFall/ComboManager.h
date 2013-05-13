#ifndef COMBOMANAGER_H
#define COMBOMANAGER_H

#include <SFML\System\Clock.hpp>

class ComboManager
{
public:
	static ComboManager* getInstance();

	void increaseComboMeter();
	void update();
	void reset(){m_comboMeter = 0;}
	unsigned int getComboMeter(){return m_comboMeter;}
	bool canActivateCombo(){return m_comboMeter >= 3;}

private:
	ComboManager();
	~ComboManager();

	sf::Clock m_clock;
	unsigned int m_comboMeter;
};

#endif