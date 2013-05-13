#include "LevelManager.h"
#include "InputManager.h"
#include "SettingsManager.h"
#include "SpriteSheetLoader.h"
#include "AudioMixer.h"

#include <iostream>

LevelManager::LevelManager(sf::View* view, sf::RenderWindow* window)
{
	m_view = view;
	m_window = window;

	m_levelObjects.push_back(new LevelObjectRectangle(2630.0f, 1710.0f, 1360.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(4310.0f, 1670.0f, 1200.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(5460.0f, 1210.0f, 160.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(6080.0f, 1480.0f, 1000.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(6080.0f, 1100.0f, 50.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(6360.0f, 1100.0f, 50.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(6670.0f, 980.0f, 50.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(7270.0f, 1480.0f, 2380.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(7700.0f, 840.0f, 1510.0f, 100.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(9900.0f, 1500.0f, 1700.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(11830.0f, 1500.0f, 1000.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(13140.0f, 1710.0f, 1350.0f, 300.0f, sf::Color::Magenta));
	m_player = new Player(2700.0f, 1300.0f, this);
	m_view->setCenter(m_player->getCenter().x
		, m_player->getCenter().y - (float)m_window->getSize().y / 3.5f);

	m_HUD = new HUD(m_view, m_player);
#pragma region Level
	sf::Sprite* tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain0", "Mountain0_0");
	tempSprite->setPosition(0.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain1", "Mountain1_0");
	tempSprite->setPosition(4096.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain2", "Mountain2_0");
	tempSprite->setPosition(5764.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain3", "Mountain3_0");
	tempSprite->setPosition(7176.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain4", "Mountain4_0");
	tempSprite->setPosition(9690.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain5", "Mountain5_0");
	tempSprite->setPosition(11694.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain6", "Mountain6_0");
	tempSprite->setPosition(13011.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);

	d_bg = SpriteSheetLoader::getInstance()->getSprite("Background", "Background_0");
	d_bg1 = new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite("Background", "Background_0"));
	d_bg->setPosition(0.0f, 0.0f);
	d_bg1->setPosition(8160.0f, 0.0f);
#pragma endregion
	m_prevCameraCenter =  m_view->getCenter();
	m_cameraMove = m_view->getCenter();

	m_enemies = new std::vector<Enemy*>();
	//m_enemies->push_back(new EnemyTroll(5460.0f, 1250.0f, m_view));
	//m_enemies->push_back(new EnemyShooter(7000.0f, 1300.0f, 100.0f, m_view));
	//m_enemies->push_back(new EnemyTroll(9000.0f, 1090.0f, m_view));
	//m_enemies->push_back(new EnemyGoblin(7500.0f, -200.0f, 1500.0f));
	//m_enemies->push_back(new EnemyShooter(9550.0f, 1300.0f, 100.0f, m_view));
	m_enemies->push_back(new EnemyTroll(11000.0f, 1100.0f, m_view));
	m_enemies->push_back(new EnemyTroll(11350.0f, 1100.0f, m_view));
	m_enemies->push_back(new EnemyShooter(11830.0f, 1200.0f, 100.0f, m_view));
	m_enemies->push_back(new EnemyShooter(12780.0f, 1200.0f, 100.0f, m_view));
	m_enemies->push_back(new EnemyGoblin(11830.0f, 300.0f, 2000.0f));
}

LevelManager::~LevelManager()
{
	delete m_HUD;

	for(unsigned int a = 0; a < m_levelObjects.size(); a++)
	{delete m_levelObjects[a];}
	delete m_player;

	for(unsigned int a = 0; a < m_enemies->size(); a++)
	{
		delete m_enemies->at(a);
	}
	delete m_enemies;

	for(unsigned int a = 0; a < m_particles.size(); a++)
	{delete m_particles[a];}
}

void LevelManager::draw(sf::RenderWindow* window)
{
	window->setView(*m_view);

	window->draw(*d_bg);
	window->draw(*d_bg1);

<<<<<<< HEAD
	for(unsigned int a = 0; a < m_backgroundSprites.size(); a++)
	{
			window->draw(*m_backgroundSprites[a]);
	}
=======


	for(unsigned int a = 0; a < m_backgroundSprites.size(); a++)
		{window->draw(*m_backgroundSprites[a]);}
>>>>>>> Level
		
	for(unsigned int a = 0; a < m_levelObjects.size(); a++)
		{m_levelObjects[a]->draw(window);}

	for(unsigned int a = 0; a < m_enemies->size(); a++)
		{m_enemies->at(a)->draw(window);}
	m_player->draw(window);

	for(unsigned int a = 0; a < m_particles.size(); a++)
	{
		m_particles[a]->draw(window);
	}

	m_HUD->draw(window);
}

void LevelManager::update(float deltaTime)
{
	for(unsigned int a = 0; a < m_particles.size();)
	{
		m_particles[a]->update(deltaTime);

		if(m_particles[a]->isEmpty())
		{
			delete m_particles[a];
			m_particles.erase(m_particles.begin() + a);
		}
		else{a++;}
	}

	//Move objects and check collision between enemies and the world
	m_player->move(deltaTime, m_levelObjects);
	for(unsigned int a = 0; a < m_enemies->size(); a++)
		{m_enemies->at(a)->move(deltaTime, m_levelObjects);}

	//Check collision between the enemies and the player
	m_player->collidesWith(m_enemies);

	//Update
	m_player->update(deltaTime);
	for(unsigned int a = 0; a < m_enemies->size(); a++)
	{m_enemies->at(a)->update(deltaTime);}

	//Update the camera's view
	m_prevCameraCenter = m_view->getCenter();

	m_view->setCenter(m_player->getCenter().x
		, m_player->getCenter().y - (float)m_window->getSize().y / 3.5f);

	if(m_view->getCenter().y < 1200.0f)
	{
		m_view->setCenter(m_view->getCenter().x, 1200.0f);
	}

	m_cameraMove = m_view->getCenter() - m_prevCameraCenter;
	m_cameraMove *= 1.25f;

	//Add bombs and projectiles
	for(unsigned int a = 0; a < m_enemies->size(); a++)
	{
		if(m_enemies->at(a)->getType() == ENEMY_GOBLIN)
		{
			if(((EnemyGoblin*)m_enemies->at(a))->shouldSpawnBomb())
			{
				m_enemies->push_back(new EnemyBomb((EnemyGoblin*)m_enemies->at(a)));
				AudioMixer::getInstance()->playSound("Bomb_falling", 0.0f, 0.0f, 70.0f, 70.0f, m_enemies->at(m_enemies->size() - 1), m_enemies->at(a)->getXPos(), m_enemies->at(a)->getYPos(), 1000.0f, 100.0f, 1.0f);
			}
		}

		else if(m_enemies->at(a)->getType() == ENEMY_SHOOTER)
		{
			if(((EnemyShooter*)m_enemies->at(a))->canShoot())
			{
				m_enemies->push_back(new EnemyProjectile((EnemyShooter*)m_enemies->at(a)));
				AudioMixer::getInstance()->playSound("Attack_shaman", 0.0f, 0.0f, 100.0f, 100.0f, m_enemies->at(a)->getXPos(), m_enemies->at(a)->getYPos(), 10.0f, 0.0f, 1.0f);
			}
		}
	}



	//Kill any object that is too far down to be alive
	if(m_player->getYPos() > 5000.0f)
	{m_player->markDead();}

	for(unsigned int a = 0; a < m_enemies->size(); a++)
	{
		if(m_enemies->at(a)->getYPos() > 5000.0f)
		{m_enemies->at(a)->markDead();}
	}

	//Delete any dead enemies
	for(unsigned int a = 0; a < m_enemies->size();)
	{
		if(m_enemies->at(a)->isDead())
		{
			delete m_enemies->at(a);
			m_enemies->erase(m_enemies->begin() + a);
		}
		else
		{
			a++;
		}

	}

	//Update the HUD
	m_HUD->update(deltaTime);
}

void LevelManager::updatePlayerSpeed()
{
	if(m_player->isDying())
	{
		return;
	}

	else if(InputManager::getInstance()->isKeyDown("P1_BLOCK"))
	{
		m_player->block(true);
	}

	else
	{
		m_player->block(false);

		//Update player speed
		if(InputManager::getInstance()->isKeyPressed("P1_MOVE_UP") && m_player->isOnGround())
		{
		AudioMixer::getInstance()->playSound("Jumping_grunt");
			m_player->increaseSpeed(0.0f, SettingsManager::getSettings()->PLAYER_SPEED_JUMP);
		}

		else if(InputManager::getInstance()->isKeyDown("P1_MOVE_DOWN") && !m_player->isOnGround())
		{
			m_player->increaseSpeed(0.0f, SettingsManager::getSettings()->PLAYER_SPEED_DOWN);
		}

		if(InputManager::getInstance()->isKeyDown("P1_MOVE_LEFT")
			&& !InputManager::getInstance()->isKeyDown("P1_MOVE_RIGHT"))
		{
			m_player->setXSpeed(-SettingsManager::getSettings()->PLAYER_SPEED_SIDE);
		}

		else if(InputManager::getInstance()->isKeyDown("P1_MOVE_RIGHT")
			&& !InputManager::getInstance()->isKeyDown("P1_MOVE_LEFT"))
		{
			m_player->setXSpeed(SettingsManager::getSettings()->PLAYER_SPEED_SIDE);
		}

		else //if(m_player->isOnGround())
		{
			m_player->haltXSpeed();
		}
	}
}

bool LevelManager::playerIsDead()
{
	return m_player->isDead();
}

void LevelManager::addParticles(sf::Vector2f position, unsigned int particles, ParticleColor color)
{
	m_particles.push_back(new ParticleSystem(position, particles, color));
}

void LevelManager::cleanResources()
{
	//Count the number of certain enemies alive
	unsigned int trollsAlive = 0;
	unsigned int goblinsAlive = 0;
	unsigned int shootersAlive = 0;

	for(unsigned int a = 0; a < m_enemies->size(); a++)
	{
		if(m_enemies->at(a)->getType() == ENEMY_TROLL)
		{
			trollsAlive++;
		}

		else if(m_enemies->at(a)->getType() == ENEMY_GOBLIN)
		{
			goblinsAlive++;
		}

		else if(m_enemies->at(a)->getType() == ENEMY_SHOOTER)
		{
			shootersAlive++;
		}
	}

	//Remove resources for enemies no longer alive
	if(trollsAlive == 0)
	{SpriteSheetLoader::getInstance()->removeSheet("Troll");}

	if(goblinsAlive == 0)
	{SpriteSheetLoader::getInstance()->removeSheet("Airship");}

	if(shootersAlive == 0)
	{SpriteSheetLoader::getInstance()->removeSheet("Shooter");}
}