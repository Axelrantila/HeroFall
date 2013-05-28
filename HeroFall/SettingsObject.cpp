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
	FRAME_VIEW_X = 2352;
	FRAME_VIEW_Y = 1470;
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
	PLAYER_KNOCKBACK_SPEED_X_INIT = 700.0f;
	PLAYER_KNOCKBACK_SPEED_X_DECREASE = 100.f;
	PLAYER_KNOCKBACK_SPEED_Y = 300.0f;
#pragma endregion

#pragma region DAMAGE
	DAMAGE_ENEMY_PLACEHOLDER_TO_PLAYER = 60.0f;
	DAMAGE_ENEMY_TROLL_TO_PLAYER = 60.0f;
	DAMAGE_PLAYER_TO_ENEMY_PLACEHOLDER = 50.0f;
	DAMAGE_PLAYER_TO_ENEMY_TROLL = 50.0f;
	DAMAGE_PLAYER_TO_ENEMY_SHOOTER = 100.0f;
	DAMAGE_ENEMY_PROJECTILE_TO_PLAYER = 35.0f;
	DAMAGE_ENEMY_BASE_TO_PLAYER = 35.0f;
	DAMAGE_PLAYER_TO_ENEMY_GOBLIN = 10.0f;
#pragma endregion

#pragma region ENEMY_TROLL
	ENEMY_TROLL_HEALTH = 125.0f;
	ENEMY_TROLL_HIT_TIME_LIMIT_MELEE = 1.0f;
	ENEMY_TROLL_SPEED_SIDE = 125.0f;
	ENEMY_TROLL_HITBOX_SIZE_X = 231.0f;
	ENEMY_TROLL_HITBOX_SIZE_Y = 330.0f;
	ENEMY_TROLL_HITBOX_LOCAL_POSITION_X = 60.0f;
	ENEMY_TROLL_HITBOX_LOCAL_POSITION_Y = 45.0f;
	ENEMY_TROLL_AI_CHANGE_LIMIT_TIME = 5.0f;
	ENEMY_TROLL_AI_WALKING_BACKWARDS_DISTANCE_LIMIT = 500.0f;
	ENEMY_TROLL_ATTACK_STAGE_1_TIME = 3.0f;
	ENEMY_TROLL_ATTACK_STAGE_2_TIME = 2.0f;
#pragma endregion

#pragma region ENEMY_GOBLIN
	ENEMY_GOBLIN_HEALTH = 1.0f;
	ENEMY_GOBLIN_SPEED_SIDE = 1000.0f;
	ENEMY_GOBLIN_BOMB_SPAWN_TIME = 1.337f;
	ENEMY_GOBLIN_BOMB_AOE_DURATION = 7.7f;
	ENEMY_GOBLIN_BOMB_BLAST_AREA_SIZE = 400.0f;
#pragma endregion

#pragma region ENEMY_SHOOTER
	ENEMY_SHOOTER_SHOOT_TIME = 4.0f;
	ENEMY_SHOOTER_PROJECTILE_PARTICLE_SPAWN_TIME = 0.1f;
	ENEMY_SHOOTER_PROJETILE_SPEED = 350.0f;
#pragma endregion

#pragma region ENEMY_BASE
	ENEMY_BASE_HEALTH = 10.0f;
	ENEMY_BASE_SPEED_BASE = 250.0f;
	ENEMY_BASE_SPEED_MIN_MULTIPLIER = 0.85f;
	ENEMY_BASE_SPEED_MAX_MULTIPLIER = 1.15f;
#pragma endregion

#pragma region PARTICLES
	PARTICLES_MAX_INIT_SPEED = 100;
#pragma endregion

#pragma region SCORE
	SCORE_KILL_TROLL = 100;
	SCORE_KILL_GOBLIN = 200;
	SCORE_KILL_SHOOTER = 300;
#pragma endregion

#pragma region HIGHSCORE
	HIGHSCORE_NAME = "";
	HIGHSCORE_SCORE = 1;
#pragma endregion
}

SettingsObject::~SettingsObject()
{
}