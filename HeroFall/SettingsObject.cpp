#include "SettingsObject.h"


SettingsObject::SettingsObject()
{
#pragma region FRAME
	FRAME_TITLE = "HeroFall";
	FRAME_FULLSCREEN = false;
	FRAME_RESOLUTION_FULLSCREEN_X = 1920;
	FRAME_RESOLUTION_FULLSCREEN_Y = 1080;
	FRAME_RESOLUTION_WINDOWED_X = 1600;
	FRAME_RESOLUTION_WINDOWED_Y = 900;
#pragma endregion

#pragma region WORLD
	WORLD_GRAVITY = 250.0f;
#pragma endregion

#pragma region PLAYER
	PLAYER_SPEED_SIDE = 200.0f;
	PLAYER_SPEED_JUMP = -200.0f;
	PLAYER_SPEED_DOWN = 15.0f;
	PLAYER_SPEED_SIDE_HALTING = 25;
	PLAYER_HEALTH = 125.0f;
	PLAYER_SWORD_SWING_TIME = 0.5f;
	PLAYER_HIT_TIME_LIMIT_MELEE = 2.0f;
#pragma endregion

#pragma region DAMAGE
	DAMAGE_ENEMY_PLACEHOLDER_TO_PLAYER = 60.0f;
	DAMAGE_PLAYER_TO_ENEMY_PLACEHOLDER = 50.0f;
#pragma endregion
}

SettingsObject::~SettingsObject()
{
}