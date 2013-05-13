#include "ComboManager.h"


ComboManager::ComboManager(void)
{
}


ComboManager::~ComboManager(void)
{
}

ComboManager* ComboManager::getInstance()
{
	static ComboManager instance;
	return &instance;
}

void ComboManager::increaseComboMeter()
{
	m_clock.restart();
	m_comboMeter++;
}

void ComboManager::update()
{
	if(m_clock.getElapsedTime().asSeconds() > 3.0f)
	{
		m_comboMeter = 0;
	}
}