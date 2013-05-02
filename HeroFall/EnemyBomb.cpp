#include "EnemyBomb.h"
#include "EnemyGoblin.h"
#include "SpriteSheetLoader.h"

EnemyBomb::EnemyBomb(EnemyGoblin* parent)
	:Enemy(ENEMY_BOMB, parent->getBombSpawnPoint().x, parent->getBombSpawnPoint().y, 1.0f)
{
	m_parent = parent;
	d_sprite = SpriteSheetLoader::getInstance()->getSprite("Bomb", "Bomb_Placeholder");
	d_sprite->setPosition(parent->getBombSpawnPoint());
}


EnemyBomb::~EnemyBomb()
{
}

void EnemyBomb::move(float delta, std::vector<LevelObject*> levelObjects)
{
	m_yVel += getGravityDistance(delta);
	m_yPos += m_yVel;
}