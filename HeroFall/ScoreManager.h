#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

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
	void resetScore(){m_totalScore = 0;}

private:
	ScoreManager();
	~ScoreManager();

	unsigned int m_totalScore;
};

#endif