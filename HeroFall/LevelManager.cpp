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
	m_levelObjects.push_back(new LevelObjectRectangle(4600.0f, 1650.0f, 5200.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(8800.0f, 1470.0f, 9500.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(9650.0f, 1180.0f, 280.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(10450.0f, 1170.0f, 555.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(14700.0f, 1170.0f, 555.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(14975.0f, 1000.0f, 260.0f, 10.0f, sf::Color::Magenta));

	m_player = new Player(14000.0f, 1000.0f, this);
	m_view->setCenter(m_player->getCenter().x
		, m_player->getCenter().y - (float)m_window->getSize().y / 3.5f);

	m_HUD = new HUD(m_view, m_player);

	sf::Sprite* tempSprite;
#pragma region LevelForest
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("ForestSegment", "ForestSegment_1");
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
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("MountainSegment_01", "Mountain_01");
	tempSprite->setPosition(8000.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("MountainSegment_02", "Mountain_02");
	tempSprite->setPosition(10328.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("MountainSegment_03", "Mountain_03");
	tempSprite->setPosition(14131.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("MountainSegment_04", "Mountain_04");
	tempSprite->setPosition(16254.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	/*tempSprite = SpriteSheetLoader::getInstance()->getSprite("01Middleground", "Bridge_01_middleground");
	tempSprite->setPosition(9850.0f, 1370.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("02Middleground", "Bridge_02_middleground");
	tempSprite->setPosition(12460.0f, 1370.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("03Middleground", "Bridge_03_middleground");
	tempSprite->setPosition(15640.0f, 1365.0f);
	m_backgroundSprites.push_back(tempSprite);*/
#pragma region ForeGround
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("MountainSegment_01", "ForeGround1");
	tempSprite->setPosition(8000.0f, 0.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("MountainSegment_02", "ForeGround2");
	tempSprite->setPosition(10328.0f, 0.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("MountainSegment_03", "ForeGround3");
	tempSprite->setPosition(14131.0f, 0.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("MountainSegment_04", "ForeGround4");
	tempSprite->setPosition(16254.0f, 0.0f);
	m_foregroundSprites.push_back(tempSprite);
	/*tempSprite = SpriteSheetLoader::getInstance()->getSprite("03Foreground", "Bridge_03_foreground");
	tempSprite->setPosition(15640.0f, 1365.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("02Foreground", "Bridge_02_foreground");
	tempSprite->setPosition(12460.0f, 1370.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("01Foreground", "Bridge_01_foreground");
	tempSprite->setPosition(9850.0f, 1370.0f);
	m_foregroundSprites.push_back(tempSprite);*/
#pragma endregion

	/*d_bg = SpriteSheetLoader::getInstance()->getSprite("Background", "Background_0");
	d_bg1 = new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite("Background", "Background_0"));
	d_bg->setPosition(0.0f, 0.0f);
	d_bg1->setPosition(8160.0f, 0.0f);*/
#pragma endregion
	m_prevCameraCenter =  m_view->getCenter();
	m_cameraMove = m_view->getCenter();

	/*m_enemies = new std::vector<Enemy*>();
	m_enemies->push_back(new EnemyTroll(1800.0f, 1300.0f, m_view));
	m_enemies->push_back(new EnemyTroll(4000.0f, 1300.0f, m_view));
	m_enemies->push_back(new EnemyShooter(5000.0f, 1250.0f, 100.0f, m_player, m_view));
	m_enemies->push_back(new EnemyTroll(6200.0f, 1250.0f, m_view));
	m_enemies->push_back(new EnemyShooter(6500.0f, 1250.0f, 100.0f, m_player, m_view));
	m_enemies->push_back(new EnemyTroll(10080.0f, 1080.0f, m_view));
	m_enemies->push_back(new EnemyShooter(9650.0f, 960.0f, 100.0f, m_player, m_view));
	m_enemies->push_back(new EnemyShooter(10850.0f, 960.0f, 100.0f, m_player, m_view));
	m_enemies->push_back(new EnemyTroll(12480.0f, 1080.0f, m_view));
	m_enemies->push_back(new EnemyGoblin(11000.0f, 200.0f, 1500.0f));
	m_enemies->push_back(new EnemyTroll(13880.0f, 1080.0f, m_view));
	m_enemies->push_back(new EnemyShooter(14000.0f, 960.0f, 100.0f, m_player, m_view));
	m_enemies->push_back(new EnemyGoblin(14400.0f, 200.0f, 1500.0f));
	m_enemies->push_back(new EnemyShooter(14700.0f, 960.0f, 100.0f, m_player, m_view));
	m_enemies->push_back(new EnemyShooter(15200.0f, 780.0f, 100.0f, m_player, m_view));
	m_enemies->push_back(new EnemyTroll(17000.0f, 1080.0f, m_view));
	m_enemies->push_back(new EnemyTroll(17400.0f, 1080.0f, m_view));*/

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

	/*window->draw(*d_bg);
	window->draw(*d_bg1);*/



	for(unsigned int a = 0; a < m_backgroundSprites.size(); a++)
		{window->draw(*m_backgroundSprites[a]);}
		
	//for(unsigned int a = 0; a < m_levelObjects.size(); a++)
	//	{m_levelObjects[a]->draw(window);}

	for(unsigned int a = 0; a < m_enemies->size(); a++)
		{m_enemies->at(a)->draw(window);}
	m_player->draw(window);

	for(unsigned int a = 0; a < m_foregroundSprites.size(); a++)
		{window->draw(*m_foregroundSprites[a]);}

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