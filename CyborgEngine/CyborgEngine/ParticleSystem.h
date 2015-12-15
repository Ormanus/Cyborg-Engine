#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "PointSprite.h"
#include <vector>

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void update(float dt);

	bool continuous = true;
	float rate = 1;
	float burstTimer = 100;
	float direction = 0;
	float dDirection = 1;
	float speed = 0.1;
	float dSpeed = 0.01;
	float lifetime = 30;
	float dLifetime = 10;
	std::string texture = "default";
private:
	std::vector<PointSprite*> particles;
	float timer = 0, x = 0, y = 0;
};



#endif