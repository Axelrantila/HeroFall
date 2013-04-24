#include <string>

#ifndef SETTINGSOBJECT_H
#define SETTINGSOBJECT_H

class SettingsObject
{
public:
	SettingsObject();
	~SettingsObject();

	/*
	READ THIS
	In this particular case, the use of public members is ok
	*/

#pragma region FRAME
	std::string		FRAME_TITLE;
	bool			FRAME_FULLSCREEN;
	unsigned int	FRAME_RESOLUTION_FULLSCREEN_X;
	unsigned int	FRAME_RESOLUTION_FULLSCREEN_Y;
	unsigned int	FRAME_RESOLUTION_WINDOWED_X;
	unsigned int	FRAME_RESOLUTION_WINDOWED_Y;
#pragma endregion

#pragma region WORLD
	float WORLD_GRAVITY;
#pragma endregion

#pragma region PLAYER
	float PLAYER_SPEED_SIDE;
	float PLAYER_SPEED_JUMP;
	float PLAYER_SPEED_DOWN;
	float PLAYER_SPEED_SIDE_HALTING;
	float PLAYER_HEALTH;
	float PLAYER_SWORD_SWING_TIME;
	float PLAYER_HIT_TIME_LIMIT_MELEE;
#pragma endregion

#pragma region DAMAGE
	float DAMAGE_ENEMY_PLACEHOLDER_TO_PLAYER;
	float DAMAGE_ENEMY_TROLL_TO_PLAYER;
	float DAMAGE_PLAYER_TO_ENEMY_PLACEHOLDER;
	float DAMAGE_PLAYER_TO_ENEMY_TROLL;
#pragma endregion

#pragma region ENEMY_TROLL
	float ENEMY_TROLL_HEALTH;
	float ENEMY_TROLL_HIT_TIME_LIMIT_MELEE;
#pragma endregion
};

#endif