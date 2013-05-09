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

	m_levelObjects.push_back(new LevelObjectRectangle(0.0f, 2160.0f, 1250.0f, 10000.0f, sf::Color::Transparent));
	m_levelObjects.push_back(new LevelObjectRectangle(1250.0f, 2060.0f, 2000.0f, 10000.0f, sf::Color::Transparent));
	//m_levelObjects.push_back(new LevelObjectRectangle(3000.0f, 1500.0f, 1250.0f, 100.0f, sf::Color::Magenta)); //Platform
	m_levelObjects.push_back(new LevelObjectRectangle(3650.0f, 2200.0f, 2250.0f, 10000.0f, sf::Color::Transparent));
	m_levelObjects.push_back(new LevelObjectRectangle(5650.0f, 2100.0f, 500.0f, 10000.0f, sf::Color::Transparent));
	m_levelObjects.push_back(new LevelObjectRectangle(6150.0f, 2100.0f, 1450.0f, 115.0f, sf::Color::Transparent));
	m_levelObjects.push_back(new LevelObjectRectangle(7550.0f, 2100.0f, 7000.0f, 10000.0f, sf::Color::Transparent));
	//m_levelObjects.push_back(new LevelObjectRectangle(8210.0f, 1800.0f, 200.0f, 50.0f, sf::Color::Transparent));
	//m_levelObjects.push_back(new LevelObjectRectangle(8450.0f, 1600.0f, 3000.0f, 300.0f, sf::Color::Magenta));
	m_player = new Player(200.0f, 1899.0f, this);
	m_view->setCenter(m_player->getCenter().x
		, m_player->getCenter().y - (float)m_window->getSize().y / 3.5f);

	//////////////////////////////////////////
	levelHouse = new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite("House", "House_0"));
	levelHouse->setPosition(8210.0f, 930.0f);
	levelBridge = new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite("Bridge", "Bridge_0"));
	levelBridge->setPosition(6150.0f, 2100.0f);
	levelBlock1 = SpriteSheetLoader::getInstance()->getSprite("Level", "Level_Grass_block1");
	levelBlock2 = SpriteSheetLoader::getInstance()->getSprite("Level", "Level_Grass_block2");
	levelBlock3 = SpriteSheetLoader::getInstance()->getSprite("Level", "Level_Grass_block3");
	levelBlock3->setPosition(5650.0f, 2100.0f);
	levelBlock4 = SpriteSheetLoader::getInstance()->getSprite("Level", "Level_Grass_block4");
	levelBlock5 = new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite("Level", "Level_Grass_block5"));
	levelBlock5->setPosition(0.0f, 2160.0f);
	levelBlock5_1 = new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite("Level", "Level_Grass_block5"));
	levelBlock5_1->setPosition(1250.0f, 2060.0f);
	levelBlock5_2 = new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite("Level", "Level_Grass_block5"));
	levelBlock5_2->setPosition(3650.0f, 2200.0f);
	levelBlock6 = SpriteSheetLoader::getInstance()->getSprite("Level", "Level_Grass_block6");
	levelBlock6->setPosition(12550.0f, 2100.0f);
	levelBlock7 = SpriteSheetLoader::getInstance()->getSprite("Level", "Level_Grass_block7");
	levelBlock8 = SpriteSheetLoader::getInstance()->getSprite("Level", "Level_Grass_block8");
	levelBlock8->setPosition(7550.0f, 2100.0f);
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	d_bg = SpriteSheetLoader::getInstance()->getSprite("Background", "Background_0");
	d_bg1 = new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite("Background", "Background_0"));
	d_bg->setPosition(0.0f, 0.0f);
	d_bg1->setPosition(8160.0f, 0.0f);

	m_prevCameraCenter =  m_view->getCenter();
	m_cameraMove = m_view->getCenter();

	m_enemies = new std::vector<Enemy*>();
	m_enemies->push_back(new EnemyTroll(2600.0f, 1679.0f, m_view));
	m_enemies->push_back(new EnemyTroll(5200.0f, 1819.0f, m_view));
	m_enemies->push_back(new EnemyTroll(7000.0f, 1719.0f, m_view));
	m_enemies->push_back(new EnemyGoblin(10000.0f, 1000.0f, 1500.0f));
	m_enemies->push_back(new EnemyShooter(10500.0f, 1940.0f, 100.0f, m_view));
}

LevelManager::~LevelManager()
{
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

	for(unsigned int a = 0; a < m_levelObjects.size(); a++)
		{m_levelObjects[a]->draw(window);}
	window->draw(*levelHouse);
	window->draw(*levelBridge);
	window->draw(*levelBlock5);
	window->draw(*levelBlock3);
	window->draw(*levelBlock5_1);
	window->draw(*levelBlock5_2);
	window->draw(*levelBlock8);
	window->draw(*levelBlock6);

	for(unsigned int a = 0; a < m_enemies->size(); a++)
		{m_enemies->at(a)->draw(window);}
	m_player->draw(window);

	for(unsigned int a = 0; a < m_particles.size(); a++)
	{
		m_particles[a]->draw(window);
	}
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
	m_player->update(deltaTime);
	m_player->move(deltaTime, m_levelObjects);

	for(unsigned int a = 0; a < m_enemies->size(); a++)
	{
		m_enemies->at(a)->update(deltaTime);
		m_enemies->at(a)->move(deltaTime, m_levelObjects);
	}

	//Check collision between the enemies and the player
	m_player->collidesWith(m_enemies);

	//Update the camera's view
	m_prevCameraCenter = m_view->getCenter();

	m_view->setCenter(m_player->getCenter().x
		, m_player->getCenter().y - (float)m_window->getSize().y / 3.5f);

	m_cameraMove = m_view->getCenter() - m_prevCameraCenter;
	m_cameraMove *= 1.25f;
	std::cout << m_cameraMove.x << " " << m_cameraMove.y << std::endl;

	//Add bombs and projectiles
	for(unsigned int a = 0; a < m_enemies->size(); a++)
	{
		if(m_enemies->at(a)->getType() == ENEMY_GOBLIN)
		{
			if(((EnemyGoblin*)m_enemies->at(a))->shouldSpawnBomb())
			{
				m_enemies->push_back(new EnemyBomb((EnemyGoblin*)m_enemies->at(a)));
			}
		}

		else if(m_enemies->at(a)->getType() == ENEMY_SHOOTER)
		{
			if(((EnemyShooter*)m_enemies->at(a))->canShoot())
			{
				m_enemies->push_back(new EnemyProjectile((EnemyShooter*)m_enemies->at(a)));
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
}

void LevelManager::updatePlayerSpeed()
{
	if(InputManager::getInstance()->isKeyDown("P1_BLOCK"))
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

		else if(m_player->isOnGround())
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