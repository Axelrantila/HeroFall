#include "ParticleSystem.h"
#include "Util.h"

ParticleSystem::ParticleSystem(sf::Vector2f position, unsigned int particles, ParticleColor color, float timeLimit)
{
	for(unsigned int a = 0; a < particles; a++)
	{
		m_particles.push_back(new Particle(position, color, timeLimit));
	}
}


ParticleSystem::~ParticleSystem(void)
{
	for(particlesIterator it = m_particles.begin(); it != m_particles.end(); ++it)
	{
		delete *it;
	}
}


void ParticleSystem::update(float delta)
{
	particlesIterator it = m_particles.begin();
	for(; it != m_particles.end();)
	{
		(*it)->update(delta);

		if((*it)->isDead())
		{
			delete (*it);
			it = m_particles.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void ParticleSystem::draw(sf::RenderWindow* window)
{
	for(particlesIterator it = m_particles.begin(); it != m_particles.end(); ++it)
	{
		window->draw(*(*it)->getSprite());
	}
}