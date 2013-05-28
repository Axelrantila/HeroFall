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
	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile("CONFIG.ini");

	if(ini.IsEmpty())
		{return false;}

	m_settings = new SettingsObject();

	m_settings->FRAME_TITLE = ini.GetValue("FRAME", "TITLE", "");
	m_settings->FRAME_FULLSCREEN = ini.GetBoolValue("FRAME", "FULLSCREEN", false);
	m_settings->FRAME_RESOLUTION_FULLSCREEN_X = ini.GetLongValue("FRAME", "RESOLUTION_FULLSCREEN_X", 0);
	m_settings->FRAME_RESOLUTION_FULLSCREEN_Y = ini.GetLongValue("FRAME", "RESOLUTION_FULLSCREEN_Y", 0);
	m_settings->FRAME_RESOLUTION_WINDOWED_X = ini.GetLongValue("FRAME", "RESOLUTION_WINDOWED_X", 0);
	m_settings->FRAME_RESOLUTION_WINDOWED_Y = ini.GetLongValue("FRAME", "RESOLUTION_WINDOWED_Y", 0);
	m_settings->FRAME_VIEW_X = ini.GetLongValue("FRAME", "VIEW_X", 0);
	m_settings->FRAME_VIEW_Y = ini.GetLongValue("FRAME", "VIEW_Y", 0);

	m_settings->WORLD_GRAVITY = (float)ini.GetDoubleValue("WORLD", "GRAVITY", 0);

	m_settings->PLAYER_SPEED_SIDE = (float)ini.GetDoubleValue("PLAYER", "SPEED_SIDE", 0);
	m_settings->PLAYER_SPEED_SIDE_HALTING = (float)ini.GetDoubleValue("PLAYER", "SPEED_SIDE_HALTING", 0);
	m_settings->PLAYER_SPEED_JUMP = (float)ini.GetDoubleValue("PLAYER", "SPEED_JUMP", 0);
	m_settings->PLAYER_SPEED_DOWN = (float)ini.GetDoubleValue("PLAYER", "SPEED_DOWN", 0);
	m_settings->PLAYER_HEALTH = (float)ini.GetDoubleValue("PLAYER", "HEALTH", 0);
	m_settings->PLAYER_SWORD_SWING_TIME = (float)ini.GetDoubleValue("PLAYER", "SWORD_SWING_TIME", 0);
	m_settings->PLAYER_HIT_TIME_LIMIT_MELEE = (float)ini.GetDoubleValue("PLAYER", "HIT_TIME_LIMIT_MELEE", 0);
	m_settings->PLAYER_KNOCKBACK_SPEED_X_INIT = (float)ini.GetDoubleValue("PLAYER", "KNOCKBACK_SPEED_X_INIT", 0);
	m_settings->PLAYER_KNOCKBACK_SPEED_X_DECREASE = (float)ini.GetDoubleValue("PLAYER", "KNOCKBACK_SPEED_X_DECREASE", 0);
	m_settings->PLAYER_KNOCKBACK_SPEED_Y = (float)ini.GetDoubleValue("PLAYER", "KNOCKBACK_SPEED_Y", 0);

	m_settings->DAMAGE_ENEMY_PLACEHOLDER_TO_PLAYER = (float)ini.GetDoubleValue("DAMAGE", "ENEMY_PLACEHOLDER_TO_PLAYER", 0);
	m_settings->DAMAGE_ENEMY_TROLL_TO_PLAYER = (float)ini.GetDoubleValue("DAMAGE", "ENEMY_TROLL_TO_PLAYER", 0);
	m_settings->DAMAGE_PLAYER_TO_ENEMY_PLACEHOLDER = (float)ini.GetDoubleValue("DAMAGE", "PLAYER_TO_ENEMY_PLACEHOLDER", 0);
	m_settings->DAMAGE_PLAYER_TO_ENEMY_TROLL = (float)ini.GetDoubleValue("DAMAGE", "PLAYER_TO_ENEMY_TROLL", 0);
	m_settings->DAMAGE_ENEMY_PROJECTILE_TO_PLAYER = (float)ini.GetDoubleValue("DAMAGE", "ENEMY_PROJECTILE_TO_PLAYER", 0);
	m_settings->DAMAGE_PLAYER_TO_ENEMY_SHOOTER = (float)ini.GetDoubleValue("DAMAGE", "PLAYER_TO_ENEMY_SHOOTER", 0);
	m_settings->DAMAGE_ENEMY_BASE_TO_PLAYER = (float)ini.GetDoubleValue("DAMAGE", "ENEMY_BASE_TO_PLAYER", 0);
	m_settings->DAMAGE_PLAYER_TO_ENEMY_GOBLIN = (float)ini.GetDoubleValue("DAMAGE", "PLAYER_TO_ENEMY_TROLL", 0);

	m_settings->ENEMY_TROLL_HEALTH = (float)ini.GetDoubleValue("ENEMY_TROLL", "HEALTH", 0);
	m_settings->ENEMY_TROLL_HIT_TIME_LIMIT_MELEE = (float)ini.GetDoubleValue("ENEMY_TROLL", "HIT_TIME_LIMIT_MELEE", 0);
	m_settings->ENEMY_TROLL_SPEED_SIDE = (float)ini.GetDoubleValue("ENEMY_TROLL", "SPEED_SIDE", 0);
	m_settings->ENEMY_TROLL_HITBOX_SIZE_X = (float)ini.GetDoubleValue("ENEMY_TROLL", "HITBOX_SIZE_X", 0);
	m_settings->ENEMY_TROLL_HITBOX_SIZE_Y = (float)ini.GetDoubleValue("ENEMY_TROLL", "HITBOX_SIZE_Y", 0);
	m_settings->ENEMY_TROLL_HITBOX_LOCAL_POSITION_X = (float)ini.GetDoubleValue("ENEMY_TROLL", "HITBOX_LOCAL_POSITION_X", 0);
	m_settings->ENEMY_TROLL_HITBOX_LOCAL_POSITION_Y = (float)ini.GetDoubleValue("ENEMY_TROLL", "HITBOX_LOCAL_POSITION_Y", 0);
	m_settings->ENEMY_TROLL_AI_CHANGE_LIMIT_TIME = (float)ini.GetDoubleValue("ENEMY_TROLL", "AI_CHANGE_LIMIT_TIME", 0);
	m_settings->ENEMY_TROLL_AI_WALKING_BACKWARDS_DISTANCE_LIMIT = (float)ini.GetDoubleValue("ENEMY_TROLL", "AI_WALKING_BACKWARDS_DISTANCE_LIMIT", 0);
	m_settings->ENEMY_TROLL_ATTACK_STAGE_1_TIME = (float)ini.GetDoubleValue("ENEMY_TROLL", "ATTACK_STAGE_1_TIME", 0);
	m_settings->ENEMY_TROLL_ATTACK_STAGE_2_TIME = (float)ini.GetDoubleValue("ENEMY_TROLL", "ATTACK_STAGE_2_TIME", 0);

	m_settings->ENEMY_GOBLIN_HEALTH = (float)ini.GetDoubleValue("ENEMY_GOBLIN", "HEALTH", 0);
	m_settings->ENEMY_GOBLIN_SPEED_SIDE = (float)ini.GetDoubleValue("ENEMY_GOBLIN", "SPEED_SIDE", 0);
	m_settings->ENEMY_GOBLIN_BOMB_SPAWN_TIME = (float)ini.GetDoubleValue("ENEMY_GOBLIN", "BOMB_SPAWN_TIME", 0);
	m_settings->ENEMY_GOBLIN_BOMB_AOE_DURATION = (float)ini.GetDoubleValue("ENEMY_GOBLIN", "BOMB_AOE_DURATION", 0);
	m_settings->ENEMY_GOBLIN_BOMB_BLAST_AREA_SIZE = (float)ini.GetDoubleValue ("ENEMY_GOBLIN", "BOMB_BLAST_AREA_SIZE", 0);

	m_settings->ENEMY_SHOOTER_SHOOT_TIME = (float)ini.GetDoubleValue("ENEMY_SHOOTER", "SHOOT_TIME", 0);
	m_settings->ENEMY_SHOOTER_PROJECTILE_PARTICLE_SPAWN_TIME = (float)ini.GetDoubleValue("ENEMY_SHOOTER", "PROJECTILE_PARTICLE_SPAWN_TIME", 0);
	m_settings->ENEMY_SHOOTER_PROJETILE_SPEED = (float)ini.GetDoubleValue("ENEMY_SHOOTER", "PROJETILE_SPEED", 0);

	m_settings->ENEMY_BASE_HEALTH = (float)ini.GetDoubleValue("ENEMY_BASE", "HEALTH", 0);
	m_settings->ENEMY_BASE_SPEED_BASE = (float)ini.GetDoubleValue("ENEMY_BASE", "SPEED_BASE", 0);
	m_settings->ENEMY_BASE_SPEED_MIN_MULTIPLIER = (float)ini.GetDoubleValue("ENEMY_BASE", "SPEED_MIN_MULTIPLIER", 0);
	m_settings->ENEMY_BASE_SPEED_MAX_MULTIPLIER = (float)ini.GetDoubleValue("ENEMY_BASE", "SPEED_MAX_MULTIPLIER", 0);

	m_settings->PARTICLES_MAX_INIT_SPEED = (float)ini.GetDoubleValue("PARTICLES", "MAX_INIT_SPEED", 0);

	m_settings->SCORE_KILL_TROLL = ini.GetLongValue("SCORE", "KILL_TROLL", 0);
	m_settings->SCORE_KILL_GOBLIN = ini.GetLongValue("SCORE", "KILL_GOBLIN", 0);
	m_settings->SCORE_KILL_SHOOTER = ini.GetLongValue("SCORE", "KILL_SHOOTER", 0);

	m_settings->HIGHSCORE_NAME = ini.GetValue("HIGHSCORE", "NAME", "");
	m_settings->HIGHSCORE_SCORE = ini.GetLongValue("HIGHSCORE", "SCORE", 0);

	return true;
}

bool SettingsManager::saveSettings()
{
	
	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile("CONFIG.ini");

	if(ini.IsEmpty())
		{return false;}

	ini.SetValue("HIGHSCORE", "NAME", m_settings->HIGHSCORE_NAME.c_str());
	ini.SetLongValue("HIGHSCORE", "SCORE", m_settings->HIGHSCORE_SCORE);

	//Save the file
	if(ini.SaveFile("CONFIG.ini") < 0)
		{return false;}
	return true;
}

SettingsObject* SettingsManager::getSettings()
{
	return getInstance()->m_settings;
}