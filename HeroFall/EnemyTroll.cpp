#include "EnemyTroll.h"


EnemyTroll::EnemyTroll(float xPos, float yPos, float health)
	:Enemy(ENEMY_TROLL, xPos, yPos, health)
{
}


EnemyTroll::~EnemyTroll()
{
}

void EnemyTroll::update(float delta)
{
}

void EnemyTroll::draw(sf::RenderWindow* window)
{
}

bool EnemyTroll::collidesWith(LevelObject* levelObject)
{
	return false;
}