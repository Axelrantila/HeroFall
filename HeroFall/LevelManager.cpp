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

	m_levelObjects.push_back(new LevelObjectRectangle(0.0f, 1750.0f, 5000.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(4600.0f, 1650.0f, 6500.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(10630.0f, 1710.0f, 1360.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(12310.0f, 1670.0f, 1200.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(13460.0f, 1210.0f, 160.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(14080.0f, 1480.0f, 1000.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(14080.0f, 1100.0f, 50.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(14360.0f, 1100.0f, 50.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(14670.0f, 980.0f, 50.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(15270.0f, 1480.0f, 2380.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(15700.0f, 840.0f, 1510.0f, 100.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(16690.0f, 440.0f, 50.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(16905.0f, 300.0f, 50.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(17195.0f, 300.0f, 50.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(17900.0f, 1500.0f, 1700.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(18390.0f, 440.0f, 50.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(18765.0f, 440.0f, 50.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(19060.0f, 840.0f, 50.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(19560.0f, 840.0f, 50.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(19830.0f, 1500.0f, 1000.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(21140.0f, 1710.0f, 1350.0f, 300.0f, sf::Color::Magenta));
	m_player = new Player(100.0f, 1500.0f, this);
	m_view->setCenter(m_player->getCenter().x
		, m_player->getCenter().y - (float)m_window->getSize().y / 3.5f);

	m_HUD = new HUD(m_view, m_player);
#pragma region LevelForest
	sf::Sprite* tempSprite = SpriteSheetLoader::getInstance()->getSprite("ForestSegment", "ForestSegment_1");
	tempSprite->setPosition(0.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("ForestSegment", "ForestSegment_2");
	tempSprite->setPosition(2000.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("ForestSegment", "ForestSegment_3");
	tempSprite->setPosition(4000.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("ForestSegment_4", "ForestSegment_4");
	tempSprite->setPosition(6000.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
#pragma endregion
#pragma region LevelMountains
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain0", "Mountain0_0");
	tempSprite->setPosition(8000.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain1", "Mountain1_0");
	tempSprite->setPosition(12096.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain2", "Mountain2_0");
	tempSprite->setPosition(13764.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain3", "Mountain3_0");
	tempSprite->setPosition(15176.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain4", "Mountain4_0");
	tempSprite->setPosition(17690.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain5", "Mountain5_0");
	tempSprite->setPosition(19694.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Mountain6", "Mountain6_0");
	tempSprite->setPosition(21011.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);

	d_bg = SpriteSheetLoader::getInstance()->getSprite("Background", "Background_0");
	d_bg1 = new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite("Background", "Background_0"));
	d_bg->setPosition(0.0f, 0.0f);
	d_bg1->setPosition(8160.0f, 0.0f);
#pragma endregion
	m_prevCameraCenter =  m_view->getCenter();
	m_cameraMove = m_view->getCenter();

	m_enemies = new std::vector<Enemy*>();
	m_enemies->push_back(new EnemyTroll(2200.0f, 1300.0f, m_view));
	m_enemies->push_back(new EnemyShooter(5000.0f, 1250.0f, 100.0f, m_player, m_view));
	m_enemies->push_back(new EnemyTroll(6000.0f, 1250.0f, m_view));
	m_enemies->push_back(new EnemyTroll(13460.0f, 1250.0f, m_view));
	m_enemies->push_back(new EnemyShooter(15000.0f, 1300.0f, 100.0f, m_player, m_view));
	m_enemies->push_back(new EnemyTroll(17000.0f, 1090.0f, m_view));
	m_enemies->push_back(new EnemyGoblin(15500.0f, -200.0f, 1500.0f));
	m_enemies->push_back(new EnemyShooter(17550.0f, 1300.0f, 100.0f, m_player, m_view));
	m_enemies->push_back(new EnemyTroll(19000.0f, 1100.0f, m_view));
	m_enemies->push_back(new EnemyTroll(19350.0f, 1100.0f, m_view));
	m_enemies->push_back(new EnemyShooter(11830.0f, 1200.0f, 100.0f, m_view));
	m_enemies->push_back(new EnemyShooter(12780.0f, 1200.0f, 100.0f, m_view));
	m_enemies->push_back(new EnemyGoblin(21830.0f, 300.0f, 2000.0f));

	for(int a = 0; a < 100; a++)
	{
		//m_enemies->push_back(new EnemyBase(3700.0f, 1300.0f, m_view));
	}

	m_popupImages = new PopupImageManager();
	m_popupImages->addImage("Base", "Base_Walk_0_0", sf::Vector2f(3700.0f, 1300.0f), sf::Vector2f(0.0f, -25.0f), 2.0f);
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

	delete m_popupImages;
}

void LevelManager::draw(sf::RenderWindow* window)
{
	window->setView(*m_view);

	window->draw(*d_bg);
	window->draw(*d_bg1);



	for(unsigned int a = 0; a < m_backgroundSprites.size(); a++)
		{window->draw(*m_backgroundSprites[a]);}
		
	//for(unsigned int a = 0; a < m_levelObjects.size(); a++)
	//	{m_levelObjects[a]->draw(window);}

	for(unsigned int a = 0; a < m_enemies->size(); a++)
		{m_enemies->at(a)->draw(window);}
	m_player->draw(window);

	for(unsigned int a = 0; a < m_particles.size(); a++)
	{
		m_particles[a]->draw(window);
	}

	m_popupImages->draw(window);
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

	//Set max view
	if(m_view->getCenter().y - m_view->getSize().y / 2.0f < 0)
	{
		m_view->setCenter(m_view->getCenter().x, m_view->getSize().y/2.0f);
	}

	m_cameraMove = m_view->getCenter() - m_prevCameraCenter;

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
				m_enemies->push_back(new EnemyProjectile((EnemyShooter*)m_enemies->at(a), this));
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

	//Update popupImages
	m_popupImages->update(deltaTime);
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
		if(m_player->blocking())
		{
			m_player->setXPos(0.0f);
		}

		else if(InputManager::getInstance()->isKeyPressed("P1_MOVE_UP") && m_player->isOnGround())
		{
		AudioMixer::getInstance()->playSound("Jumping_grunt");
			m_player->increaseSpeed(0.0f, SettingsManager::getSettings()->PLAYER_SPEED_JUMP);
		}

		else if((InputManager::getInstance()->isKeyDown("P1_MOVE_DOWN") || !InputManager::getInstance()->isKeyDown("P1_MOVE_UP"))&& !m_player->isOnGround())
		{
			m_player->increaseSpeed(0.0f, SettingsManager::getSettings()->PLAYER_SPEED_DOWN);
		}

		if(InputManager::getInstance()->isKeyDown("P1_MOVE_LEFT")
			&& !InputManager::getInstance()->isKeyDown("P1_MOVE_RIGHT")
			&& !m_player->blocking())
		{
			m_player->setXSpeed(-SettingsManager::getSettings()->PLAYER_SPEED_SIDE);
		}

		else if(InputManager::getInstance()->isKeyDown("P1_MOVE_RIGHT")
			&& !InputManager::getInstance()->isKeyDown("P1_MOVE_LEFT")
			&& !m_player->blocking())
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

void LevelManager::addParticles(sf::Vector2f position, unsigned int particles, ParticleColor color, float timeLimit)
{
	m_particles.push_back(new ParticleSystem(position, particles, color, timeLimit));
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