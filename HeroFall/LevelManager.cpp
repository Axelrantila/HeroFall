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

	m_levelObjects.push_back(new LevelObjectRectangle(0.0f, 0.0f, 1.0f, 1700.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(0.0f, 1680.0f, 4700.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(4700.0f, 1600.0f, 1500.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(6200.0f, 1470.0f, 1820.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(8320.0f, 1460.0f, 1560.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(9610.0f, 1170.0f, 280.0f, 40.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(10050.0f, 1320.0f, 280.0f, 40.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(10400.0f, 1460.0f, 2420.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(10500.0f, 1110.0f, 555.0f, 40.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(13000.0f, 1630.0f, 280.0f, 40.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(13400.0f, 1700.0f, 280.0f, 40.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(13800.0f, 1550.0f, 280.0f, 40.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(14200.0f, 1460.0f, 3900.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(14660.0f, 1110.0f, 555.0f, 40.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(14940.0f, 770.0f, 260.0f, 40.0f, sf::Color::Magenta));

	m_levelObjects.push_back(new LevelObjectRectangle(18100.0f, 1760.0f, 1260.0f, 500.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(19560.0f, 2170.0f, 3060.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(20950.0f, 1600.0f, 1000.0f, 100.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(22300.0f, 1970.0f, 1170.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(23470.0f, 2270.0f, 5000.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(24770.0f, 2040.0f, 250.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(23800.0f, 1570.0f, 180.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(24000.0f, 1240.0f, 920.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(24920.0f, 1500.0f, 140.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(25170.0f, 1240.0f, 1580.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(25280.0f, 1250.0f, 1300.0f, 400.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(25100.0f, 1780.0f, 180.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(27060.0f, 1500.0f, 1140.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(27300.0f, 880.0f, 640.0f, 100.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(28420.0f, 2070.0f, 4700.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(31100.0f, 1300.0f, 1780.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(29030.0f, 1870.0f, 200.0f, 200.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(29830.0f, 1890.0f, 200.0f, 180.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(29470.0f, 1710.0f, 200.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(30060.0f, 1500.0f, 200.0f, 600.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(33090.0f, 2340.0f, 200.0f, 300.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(33290.0f, 2620.0f, 500.0f, 10.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(33680.0f, 2070.0f, 2000.0f, 600.0f, sf::Color::Magenta));
	m_levelObjects.push_back(new LevelObjectRectangle(33680.0f, 1970.0f, 100.0f, 100.0f, sf::Color::Magenta));

	m_player = new Player(18200.0f, 800.0f, this);
	m_view->setCenter(m_player->getCenter().x
		, m_player->getCenter().y - (float)m_window->getSize().y / 3.5f);

	m_HUD = new HUD(m_view, m_player);
    sf::Sprite* tempSprite;



#pragma region LevelMountains
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("MountainSegment_01", "Mountain_01");
	tempSprite->setPosition(8000.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("MountainSegment_02", "Mountain_02");
	tempSprite->setPosition(10328.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("MountainSegment_03", "Mountain_03");
	tempSprite->setPosition(14131.0f, 20.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("MountainSegment_04", "Mountain_04");
	tempSprite->setPosition(16255.0f, 0.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Banner_02", "Banner_02");
	tempSprite->setPosition(9840.0f, 1210.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("01Middleground", "Bridge_01_middleground");
	tempSprite->setPosition(9880.0f, 1370.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Banner_02", "Banner_02");
	tempSprite->setPosition(10480.0f, 1210.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Banner_02", "Banner_02");
	tempSprite->setPosition(12420.0f, 1210.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("02Middleground", "Bridge_02_middleground");
	tempSprite->setPosition(12460.0f, 1370.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Banner_02", "Banner_02");
	tempSprite->setPosition(13600.0f, 1210.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Banner_02", "Banner_02");
	tempSprite->setPosition(15600.0f, 1210.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("03Middleground", "Bridge_03_middleground");
	tempSprite->setPosition(15640.0f, 1365.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Banner_02", "Banner_02");
	tempSprite->setPosition(16960.0f, 1210.0f);
	m_backgroundSprites.push_back(tempSprite);
#pragma endregion
#pragma region ForeGround
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_01", "Foreground_01_leg");
	tempSprite->setPosition(7290.0f, 280.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_01", "Foreground_01_top");
	tempSprite->setPosition(7290.0f, 280.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_03_2", "Foreground_03_2_Top");
	tempSprite->setPosition(10050.0f, 1250.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_03_2", "Foreground_03_2_Leg");
	tempSprite->setPosition(10050.0f, 1250.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_02_leg", "Foreground_2");
	tempSprite->setPosition(10500.0f, 1060.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_02_top", "Foreground_1");
	tempSprite->setPosition(10500.0f, 1060.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_03_2", "Foreground_03_2_Leg");
	tempSprite->setPosition(13000.0f, 1580.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_03_2", "Foreground_03_2_Top");
	tempSprite->setPosition(13000.0f, 1580.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_03_2", "Foreground_03_2_Leg");
	tempSprite->setPosition(13400.0f, 1650.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_03_2", "Foreground_03_2_Top");
	tempSprite->setPosition(13400.0f, 1650.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_03_2", "Foreground_03_2_Leg");
	tempSprite->setPosition(13800.0f, 1500.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_03_2", "Foreground_03_2_Top");
	tempSprite->setPosition(13800.0f, 1500.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_03", "Foreground_03_legs");
	tempSprite->setPosition(14660.0f, 640.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_03", "Foreground_03_Top");
	tempSprite->setPosition(14660.0f, 640.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Foreground_04", "Foreground_04");
	tempSprite->setPosition(16254.0f, 0.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("03Foreground", "Bridge_03_foreground");
	tempSprite->setPosition(15640.0f, 1430.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("02Foreground", "Bridge_02_foreground");
	tempSprite->setPosition(12460.0f, 1430.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("01Foreground", "Bridge_01_foreground");
	tempSprite->setPosition(9880.0f, 1430.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Banner_02", "Banner_02");
	tempSprite->setPosition(9840.0f, 1290.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Banner_02", "Banner_02");
	tempSprite->setPosition(10480.0f, 1290.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Banner_02", "Banner_02");
	tempSprite->setPosition(12420.0f, 1290.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Banner_02", "Banner_02");
	tempSprite->setPosition(14600.0f, 1290.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Banner_02", "Banner_02");
	tempSprite->setPosition(15600.0f, 1290.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("Banner_02", "Banner_02");
	tempSprite->setPosition(16960.0f, 1290.0f);
	m_foregroundSprites.push_back(tempSprite);
#pragma endregion
#pragma region LevelForest
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("ForestSegment", "forestSegment_01");
	tempSprite->setPosition(0.0f, 640.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("ForestSegment_1_1", "forestSegment_bridge_front");
	tempSprite->setPosition(1290.0f, 1600.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("ForestSegment_1_2", "forestSegment1_bridge_back");
	tempSprite->setPosition(1290.0f, 1620.0f);
	m_foregroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("ForestSegment", "forestSegment_02");
	tempSprite->setPosition(1900.0f, 640.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("ForestSegment", "forestSegment_03");
	tempSprite->setPosition(3800.0f, 640.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("ForestSegment", "forestSegment_04");
	tempSprite->setPosition(5700.0f, 640.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("ForestSegment_5_1", "forestSegment_5_bridge_back");
	tempSprite->setPosition(7500.0f, 1380.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("ForestSegment_5_2", "forestSegment_5_bridge_front");
	tempSprite->setPosition(7502.0f, 1420.0f);
	m_foregroundSprites.push_back(tempSprite);
#pragma endregion
#pragma region LevelTown
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("TownSegment_02", "townSegment_02");
	tempSprite->setPosition(18370.0f, 950.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("townSegment_bridgeFromMountain", "bridge_from_mountain");
	tempSprite->setPosition(18140.0f, 1720.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("TownSegment_03", "TownSegment_03");
	tempSprite->setPosition(19560.0f, 1000.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("TownSegment_04", "TownSegment_04");
	tempSprite->setPosition(22300.0f, 1400.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("TownSegment_05", "TownSegment_05_temp2");
	tempSprite->setPosition(23471.0f, 800.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("townSegment_bjalke", "townSegment_bjalke_mirror");
	tempSprite->setPosition(23800.0f, 1560.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("townSegment_bjalke", "townSegment_bjalke_short");
	tempSprite->setPosition(24850.0f, 1500.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("townSegment_bjalke", "townSegment_bjalke_short_mirror");
	tempSprite->setPosition(25030.0f, 1780.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("TownSegment_box", "townSegment_box");
	tempSprite->setPosition(24471.0f, 2000.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("TownSegment_06", "TownSegment_06");
	tempSprite->setPosition(28423.0f, 960.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("TownSegment_07", "TownSegment_07");
	tempSprite->setPosition(30520.0f, 1080.0f);
	m_backgroundSprites.push_back(tempSprite);
	tempSprite = SpriteSheetLoader::getInstance()->getSprite("TownSegment_08", "TownSegment_08");
	tempSprite->setPosition(33554.0f, 1070.0f);
	m_backgroundSprites.push_back(tempSprite);
#pragma endregion
	m_prevCameraCenter =  m_view->getCenter();
	m_cameraMove = m_view->getCenter();

	m_enemies = new std::vector<Enemy*>();
	/*m_enemies->push_back(new EnemyTroll(3800.0f, 1200.0f, m_view));
	m_enemies->push_back(new EnemyTroll(5200.0f, 1000.0f, m_view));
	m_enemies->push_back(new EnemyBase(1800.0f, 1000.0f, m_view));
	m_enemies->push_back(new EnemyShooter(4700.0f, 1200.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyTroll(9000.0f, 1000.0f, m_view));
	m_enemies->push_back(new EnemyShooter(6200.0f, 1250.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyShooter(9600.0f, 900.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyShooter(10480.0f, 900.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyShooter(10950.0f, 900.0f, 100.0f, m_player, DIR_RIGHT, m_view));
	m_enemies->push_back(new EnemyTroll(12440.0f, 1020.0f, m_view));
	m_enemies->push_back(new EnemyGoblin(11000.0f, 0.0f, 1500.0f));
	m_enemies->push_back(new EnemyTroll(14200.0f, 1020.0f, m_view));
	m_enemies->push_back(new EnemyShooter(13800.0f, 960.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyGoblin(15400.0f, 0.0f, 1500.0f));
	m_enemies->push_back(new EnemyShooter(14650.0f, 900.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyShooter(15100.0f, 400.0f, 100.0f, m_player, DIR_RIGHT, m_view));
	m_enemies->push_back(new EnemyTroll(17000.0f, 1020.0f, m_view));
	m_enemies->push_back(new EnemyTroll(17400.0f, 1020.0f, m_view));
	m_enemies->push_back(new EnemyTroll(18700.0f, 1020.0f, m_view));
	m_enemies->push_back(new EnemyShooter(20920.0f, 900.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyTroll(21400.0f, 1620.0f, m_view));
	m_enemies->push_back(new EnemyShooter(21860.0f, 900.0f, 100.0f, m_player, DIR_RIGHT, m_view));

	m_enemies->push_back(new EnemyTroll(23000.0f, 1420.0f, m_view));
	m_enemies->push_back(new EnemyShooter(22260.0f, 900.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyShooter(23980.0f, 900.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyShooter(23800.0f, 1000.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyShooter(24760.0f, 1600.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyTroll(24420.0f, 700.0f, m_view));
	m_enemies->push_back(new EnemyGoblin(24400.0f, 0.0f, 1500.0f));
	m_enemies->push_back(new EnemyTroll(26000.0f, 700.0f, m_view));
	m_enemies->push_back(new EnemyShooter(26620.0f, 700.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyShooter(27300.0f, 700.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyShooter(27820.0f, 700.0f, 100.0f, m_player, DIR_RIGHT, m_view));
	m_enemies->push_back(new EnemyTroll(27400.0f, 1820.0f, m_view));
	m_enemies->push_back(new EnemyShooter(28000.0f, 1820.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyTroll(27400.0f, 1000.0f, m_view));
	m_enemies->push_back(new EnemyShooter(28000.0f, 1220.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyShooter(29420.0f, 1220.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyTroll(29300.0f, 1620.0f, m_view));
	m_enemies->push_back(new EnemyShooter(30020.0f, 700.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyShooter(31080.0f, 900.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyShooter(32780.0f, 900.0f, 100.0f, m_player, DIR_RIGHT, m_view));
	m_enemies->push_back(new EnemyShooter(33660.0f, 900.0f, 100.0f, m_player, DIR_LEFT, m_view));
	m_enemies->push_back(new EnemyTroll(31000.0f, 1620.0f, m_view));
	m_enemies->push_back(new EnemyTroll(32000.0f, 1620.0f, m_view));
	m_enemies->push_back(new EnemyTroll(30300.0f, 1620.0f, m_view));*/

	m_popupImages = new PopupImageManager();
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

	for(unsigned int a = 0; a < m_backgroundLayer.size(); a++)
		{window->draw(*m_backgroundLayer[a]);}
	for(unsigned int a = 0; a < m_backMidgroundLayer.size(); a++)
		{window->draw(*m_backMidgroundLayer[a]);}
	for(unsigned int a = 0; a < m_midgroundLayer.size(); a++)
		{window->draw(*m_midgroundLayer[a]);}
	for(unsigned int a = 0; a < m_foreMidgroundLayer.size(); a++)
		{window->draw(*m_foreMidgroundLayer[a]);}

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

	if(m_view->getCenter().x - m_view->getSize().x / 2.0f < 0.0f)
	{
		m_view->setCenter(m_view->getSize().x / 2.0f, m_view->getCenter().y);
	}

	//Set max view
	if(m_view->getCenter().y - m_view->getSize().y / 2.0f < 0)
	{
		m_view->setCenter(m_view->getCenter().x, m_view->getSize().y/2.0f);
	}

	if(m_view->getCenter().y > 1500.0f)
	{
		m_view->setCenter(m_view->getCenter().x, 1500.0f);
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

	else if(m_player->isKnockedBack())
	{
		m_player->block(false);
	}

	else if(InputManager::getInstance()->isKeyDown("P1_BLOCK") && !m_player->attacking())
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

		else if((InputManager::getInstance()->isKeyDown("P1_MOVE_DOWN") || !InputManager::getInstance()->isKeyDown("P1_MOVE_UP"))
			&& !m_player->isOnGround())
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

void LevelManager::addPopupImage(std::string sheetName, std::string spriteName, sf::Vector2f position, sf::Vector2f speed, float maxTime)
{
	m_popupImages->addImage(sheetName, spriteName, position, speed, maxTime);
}