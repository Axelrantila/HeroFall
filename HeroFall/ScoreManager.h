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

private:
	ScoreManager();
	~ScoreManager();

	unsigned int m_totalScore;
};

#endif