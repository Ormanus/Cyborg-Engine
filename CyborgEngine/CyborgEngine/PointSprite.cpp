#include "PointSprite.h"

PointSprite::PointSprite(float x, float y, std::string texture)
	:x(x), y(y), texture(texture)
{
	printf_s("constructing...\n", "");
}

PointSprite::~PointSprite()
{
	printf_s("destructing...\n", "");
}

void PointSprite::update()
{
	x += hspeed;
	y += vspeed;
}
void PointSprite::setMovement(float speed, float direction)
{
	hspeed = cos(direction) * speed;
	vspeed = sin(direction) * speed;
}