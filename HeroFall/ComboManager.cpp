#include "ComboManager.h"


ComboManager::ComboManager(void)
{
	m_comboMeter = 0.0f;
}


ComboManager::~ComboManager(void)
{
}

ComboManager* ComboManager::getInstance()
{
	static ComboManager instance;
	return &instance;
}

void ComboManager::update(float delta)
{
	m_comboMeter -= delta;

	if(m_comboMeter < 0.0f)
		{m_comboMeter = 0.0f;}
}

void ComboManager::increaseComboMeter()
{
	m_comboMeter += 2.5f;
}