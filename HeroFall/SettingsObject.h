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
#pragma endregion
};

#endif