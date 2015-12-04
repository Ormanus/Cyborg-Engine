#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>

class Particle
{
public:
	Particle(float x, float y, std::string texture);
	std::string getTexture(){ return texture; }

	~Particle();
private:
	float x, y, time;
	std::string texture;
};
#endif