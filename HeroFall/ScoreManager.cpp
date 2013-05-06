#include "ScoreManager.h"
#include "SettingsManager.h"

ScoreManager::ScoreManager()
{
	m_totalScore = 0;
}


ScoreManager::~ScoreManager()
{
}

ScoreManager* ScoreManager::getInstance()
{
	static ScoreManager instance;
	return &instance;
}

void ScoreManager::addScore(KillEnum type)
{
	if(type == KILL_TROLL)
	{
		m_totalScore += SettingsManager::getSettings()->SCORE_KILL_TROLL;
	}
}