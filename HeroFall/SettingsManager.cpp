#include <SimpleINI\SimpleIni.h>

#include "SettingsManager.h"

SettingsManager* SettingsManager::getInstance()
{
	static SettingsManager instance;
	return &instance;
}

SettingsManager::SettingsManager()
{
	loadSettings();
}

SettingsManager::~SettingsManager()
{
	saveSettings();
	delete m_settings;
}

bool SettingsManager::loadSettings()
{
	m_settings = new SettingsObject();

	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile("CONFIG.ini");

	if(ini.IsEmpty())
		{return false;}

	m_settings->FRAME_TITLE = ini.GetValue("FRAME", "TITLE", "");
	m_settings->FRAME_FULLSCREEN = ini.GetBoolValue("FRAME", "FULLSCREEN", false);
	m_settings->FRAME_RESOLUTION_FULLSCREEN_X = ini.GetLongValue("FRAME", "RESOLUTION_FULLSCREEN_X", 0);
	m_settings->FRAME_RESOLUTION_FULLSCREEN_Y = ini.GetLongValue("FRAME", "RESOLUTION_FULLSCREEN_Y", 0);
	m_settings->FRAME_RESOLUTION_WINDOWED_X = ini.GetLongValue("FRAME", "RESOLUTION_WINDOWED_X", 0);
	m_settings->FRAME_RESOLUTION_WINDOWED_Y = ini.GetLongValue("FRAME", "RESOLUTION_WINDOWED_Y", 0);

	m_settings->WORLD_GRAVITY = (float)ini.GetDoubleValue("WORLD", "GRAVITY", 0);

	m_settings->PLAYER_SPEED_SIDE = (float)ini.GetDoubleValue("PLAYER", "SPEED_SIDE", 0);
	m_settings->PLAYER_SPEED_SIDE_HALTING = (float)ini.GetDoubleValue("PLAYER", "SPEED_SIDE_HALTING", 0);
	m_settings->PLAYER_SPEED_JUMP = (float)ini.GetDoubleValue("PLAYER", "SPEED_JUMP", 0);
	m_settings->PLAYER_SPEED_DOWN = (float)ini.GetDoubleValue("PLAYER", "SPEED_DOWN", 0);
	m_settings->PLAYER_HEALTH = (float)ini.GetDoubleValue("PLAYER", "HEALTH", 0);
	m_settings->PLAYER_SWORD_SWING_TIME = (float)ini.GetDoubleValue("PLAYER", "SWORD_SWING_TIME", 0);
	m_settings->PLAYER_HIT_TIME_LIMIT_MELEE = (float)ini.GetDoubleValue("PLAYER", "HIT_TIME_LIMIT_MELEE", 0);

	m_settings->DAMAGE_ENEMY_PLACEHOLDER_TO_PLAYER = (float)ini.GetDoubleValue("DAMAGE", "ENEMY_PLACEHOLDER_TO_PLAYER", 0);
	m_settings->DAMAGE_ENEMY_TROLL_TO_PLAYER = (float)ini.GetDoubleValue("DAMAGE", "ENEMY_TROLL_TO_PLAYER", 0);
	m_settings->DAMAGE_PLAYER_TO_ENEMY_PLACEHOLDER = (float)ini.GetDoubleValue("DAMAGE", "PLAYER_TO_ENEMY_PLACEHOLDER", 0);
	m_settings->DAMAGE_PLAYER_TO_ENEMY_TROLL = (float)ini.GetDoubleValue("DAMAGE", "PLAYER_TO_ENEMY_TROLL", 0);

	m_settings->ENEMY_TROLL_HEALTH = (float)ini.GetDoubleValue("ENEMY_TROLL", "HEALTH", 0);
	m_settings->ENEMY_TROLL_HIT_TIME_LIMIT_MELEE = (float)ini.GetDoubleValue("ENEMY_TROLL", "HIT_TIME_LIMIT_MELEE", 0);

	return true;
}

bool SettingsManager::saveSettings()
{
	return true;
}

SettingsObject* SettingsManager::getSettings()
{
	return getInstance()->m_settings;
}