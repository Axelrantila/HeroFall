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
	unsigned int	FRAME_VIEW_X;
	unsigned int	FRAME_VIEW_Y;
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
	float PLAYER_KNOCKBACK_SPEED_X_INIT;
	float PLAYER_KNOCKBACK_SPEED_X_DECREASE;
	float PLAYER_KNOCKBACK_SPEED_Y;
#pragma endregion

#pragma region DAMAGE
	float DAMAGE_ENEMY_PLACEHOLDER_TO_PLAYER;
	float DAMAGE_ENEMY_TROLL_TO_PLAYER;
	float DAMAGE_PLAYER_TO_ENEMY_PLACEHOLDER;
	float DAMAGE_PLAYER_TO_ENEMY_TROLL;
	float DAMAGE_PLAYER_TO_ENEMY_SHOOTER;
	float DAMAGE_ENEMY_PROJECTILE_TO_PLAYER;
	float DAMAGE_ENEMY_BASE_TO_PLAYER;
	float DAMAGE_PLAYER_TO_ENEMY_GOBLIN;
#pragma endregion

#pragma region ENEMY_TROLL
	float ENEMY_TROLL_HEALTH;
	float ENEMY_TROLL_HIT_TIME_LIMIT_MELEE;
	float ENEMY_TROLL_SPEED_SIDE;
	float ENEMY_TROLL_HITBOX_SIZE_X;
	float ENEMY_TROLL_HITBOX_SIZE_Y;
	float ENEMY_TROLL_HITBOX_LOCAL_POSITION_X;
	float ENEMY_TROLL_HITBOX_LOCAL_POSITION_Y;
	float ENEMY_TROLL_AI_CHANGE_LIMIT_TIME;
	float ENEMY_TROLL_AI_WALKING_BACKWARDS_DISTANCE_LIMIT;
	float ENEMY_TROLL_ATTACK_STAGE_1_TIME;
	float ENEMY_TROLL_ATTACK_STAGE_2_TIME;
#pragma endregion

#pragma region ENEMY_GOBLIN
	float ENEMY_GOBLIN_HEALTH;
	float ENEMY_GOBLIN_SPEED_SIDE;
	float ENEMY_GOBLIN_BOMB_SPAWN_TIME;
	float ENEMY_GOBLIN_BOMB_AOE_DURATION;
	float ENEMY_GOBLIN_BOMB_BLAST_AREA_SIZE;
#pragma endregion

#pragma region ENEMY_SHOOTER
	float ENEMY_SHOOTER_SHOOT_TIME;
	float ENEMY_SHOOTER_PROJECTILE_PARTICLE_SPAWN_TIME;
	float ENEMY_SHOOTER_PROJETILE_SPEED;
	float ENEMY_SHOOTER_PROJECTILE_LIFE_TIME;
#pragma endregion

#pragma region ENEMY_BASE
	float ENEMY_BASE_HEALTH;
	float ENEMY_BASE_SPEED_BASE;
	float ENEMY_BASE_SPEED_MIN_MULTIPLIER;
	float ENEMY_BASE_SPEED_MAX_MULTIPLIER;
#pragma endregion

#pragma region PARTICLES
	float PARTICLES_MAX_INIT_SPEED;
#pragma endregion

#pragma region SCORE
	unsigned int SCORE_KILL_TROLL;
	unsigned int SCORE_KILL_GOBLIN;
	unsigned int SCORE_KILL_SHOOTER;
	unsigned int SCORE_KILL_BASE;
	float SCORE_TIME_LIMIT;
#pragma endregion

#pragma region HIGHSCORE
	std::string HIGHSCORE_NAME;
	std::string HIGHSCORE2_NAME;
	std::string HIGHSCORE3_NAME;

	unsigned int HIGHSCORE_SCORE;
	unsigned int HIGHSCORE2_SCORE;
	unsigned int HIGHSCORE3_SCORE;
#pragma endregion
};

#endif