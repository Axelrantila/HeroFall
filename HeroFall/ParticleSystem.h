#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Particle.h"

typedef std::vector<Particle*>::iterator particlesIterator;

class ParticleSystem
{
public:
	ParticleSystem(sf::Vector2f position, unsigned int particles, ParticleColor color = PARTICLE_COLOR_RED, float timeLimit = 5.0f);
	~ParticleSystem();

	void update(float delta);
	void draw(sf::RenderWindow* window);

	bool isEmpty(){return m_particles.empty();}
private:
	std::vector<Particle*> m_particles;
};

#endif