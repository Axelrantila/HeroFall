#ifndef ENEMYBOMB_H
#define ENEMYBOMB_H

#include "AnimationManager.h"
#include "Enemy.h"

class EnemyGoblin;

class EnemyBomb
	:public Enemy
{
public:
	EnemyBomb(EnemyGoblin* parent);
	~EnemyBomb();

	void move(float delta, std::vector<LevelObject*> levelObjects);
	void update(float delta);
	void draw(sf::RenderWindow* window);
	bool collidesWith(LevelObject* levelObject);

	sf::FloatRect getGlobalBounds();
	bool hasBlased(){return m_bombHasBlasted;}

private:
	sf::Sprite* m_sprite;
	AnimationManager* m_animations;

	bool m_bombHasBlasted;
	sf::RectangleShape m_bombBlastArea;
	float m_bombBlastCurrentTime;
	float m_bombBlastTotalTime;
};

#endif