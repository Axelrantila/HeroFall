#include "Particle.h"
#include "SettingsManager.h"
#include "SpriteSheetLoader.h"
#include "Util.h"

Particle::Particle(sf::Vector2f position, ParticleColor color, float timeLimit)
{
	m_position = position;

	m_velocity.x = Util::getInstance()->getRandomFloat(-SettingsManager::getSettings()->PARTICLES_MAX_INIT_SPEED, SettingsManager::getSettings()->PARTICLES_MAX_INIT_SPEED);
	m_velocity.y = Util::getInstance()->getRandomFloat(-SettingsManager::getSettings()->PARTICLES_MAX_INIT_SPEED, SettingsManager::getSettings()->PARTICLES_MAX_INIT_SPEED);

	m_gravity.x = Util::getInstance()->getRandomFloat(-SettingsManager::getSettings()->WORLD_GRAVITY, SettingsManager::getSettings()->WORLD_GRAVITY);
	m_gravity.y = Util::getInstance()->getRandomFloat(-SettingsManager::getSettings()->WORLD_GRAVITY, SettingsManager::getSettings()->WORLD_GRAVITY);

	if(color == PARTICLE_COLOR_RED)
	{
		m_sprite = new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite("Particle", "Particle_Red"));
	}

	else if(color == PARTICLE_COLOR_BLOOD)
	{
		m_sprite = new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite("Particle", "Particle_Blood"));
	}

	else if(color == PARTICLE_COLOR_FIRE)
	{
		m_sprite = new sf::Sprite(*SpriteSheetLoader::getInstance()->getSprite("Particle", "Particle_Fire"));
	}

	m_timeElapsed = 0.0f;
	m_timeLimit = Util::getInstance()->getRandomFloat(1.0f, timeLimit);
}

Particle::~Particle()
{
	delete m_sprite;
}

void Particle::update(float delta)
{
	m_timeElapsed += delta;

	//Update velocity
	m_velocity.x += delta * m_gravity.x;
	m_velocity.y += delta * m_gravity.y;

	//Update position
	m_position.x += m_velocity.x * delta;
	m_position.y += m_velocity.y * delta;

	m_sprite->setPosition(m_position.x, m_position.y);
}