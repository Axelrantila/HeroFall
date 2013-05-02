#include "EnemyBomb.h"
#include "EnemyGoblin.h"
#include "SpriteSheetLoader.h"

EnemyBomb::EnemyBomb(EnemyGoblin* parent)
	:Enemy(ENEMY_BOMB, parent->getBombSpawnPoint().x, parent->getBombSpawnPoint().y, 1.0f)
{
	m_parent = parent;
	d_sprite = SpriteSheetLoader::getInstance()->getSprite("Bomb", "Bomb_Placeholder");
	d_sprite->setPosition(parent->getBombSpawnPoint());

	m_yVel = 0.0f;
	m_xVel = 0.0f;
}


EnemyBomb::~EnemyBomb()
{
}

void EnemyBomb::move(float delta, std::vector<LevelObject*> levelObjects)
{
	m_yVel += getGravityDistance(delta);
	m_yPos += m_yVel * delta;
	d_sprite->setPosition(m_xPos, m_yPos);
}

void EnemyBomb::draw(sf::RenderWindow* window)
{
	window->draw(*d_sprite);
}

sf::FloatRect EnemyBomb::getGlobalBounds()
{
	return d_sprite->getGlobalBounds();
}