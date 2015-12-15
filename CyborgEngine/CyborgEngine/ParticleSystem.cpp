#include "ParticleSystem.h"
#include "Renderer.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update(float dt)
{
	//update particles
	for (int i = 0; i < particles.size(); i++)
	{
		PointSprite* p = particles[i];
		if (p == nullptr)
		{
			std::cout << "NULL!\n";
			continue;
		}
		Renderer::drawPointSprite(1, p);
		p->setTime(p->getTime()-dt);
		if (p->getTime() < 0)
		{
			std::cout << "deleting\n";
			delete p;
			p = nullptr;
		}
	}
	//delete particles
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i] == nullptr)
		{
			swap(particles.begin()+1, particles.end());


			std::cout << "removing...\n";
			//particles.erase(particles.begin()+i);
			i--; 
			particles.pop_back();

			std::cout << "particle removed\n";
		}
	}
	if (rate > 0)
	{
		if (burstTimer > 0)
		{
			//create particles
			while (timer > 1)
			{
				timer -= 1 / rate;
				PointSprite* p = new PointSprite(x, y, "part");
				float s = speed + (float)(rand() % 1000) / 1000 * dSpeed;
				float d = direction + (float)(rand() % 1000) / 1000 * dDirection;
				float t = lifetime + (float)(rand() % 1000) / 1000 * dLifetime;
				p->setPosition(0.5, 0.5);
				p->setMovement(s, d);
				p->setTime(t);
				particles.push_back(p);
				std::cout << "particle created\n";
			}
			timer += dt;
			if (!continuous)
				burstTimer -= dt;
		}
	}
}