#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\Graphics.hpp>

enum ParticleColor
{
	PARTICLE_COLOR_RED,
	PARTICLE_COLOR_BLOOD,
	PARTICLE_COLOR_FIRE
};

class Particle
{
public:
	Particle(sf::Vector2f position, ParticleColor color);
	~Particle();

	void update(float delta);
	bool isDead(){return m_timeElapsed > m_timeLimit;}

	sf::Sprite* getSprite(){return m_sprite;}

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_gravity;
	sf::Sprite* m_sprite;

	float m_timeElapsed;
	float m_timeLimit;
};

#endif