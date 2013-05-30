#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <SFML\System\Clock.hpp>

enum KillEnum
{
	KILL_TROLL,
	KILL_GOBLIN,
	KILL_SHOOTER
};

class ScoreManager
{
public:
	static ScoreManager* getInstance();

	void addScore(KillEnum type);
	unsigned int getScore(){return m_totalScore;}
	void resetScore();

	unsigned int getVictoryScore();

private:
	ScoreManager();
	~ScoreManager();

	unsigned int m_totalScore;

	sf::Clock m_clock;
};

#endif