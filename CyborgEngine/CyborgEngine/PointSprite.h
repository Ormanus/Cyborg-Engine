#ifndef P_SPRITE_H
#define P_SPRITE_H

#include <string>

class PointSprite
{
public:
	PointSprite(float x, float y, std::string texture);
	std::string getTexture(){ return texture; }
	void setPosition(float x, float y){ this->x = x; this->y = y; }
	void setMovement(float speed, float direction);
	void setTime(float time){ this->time = time; }
	float getX(){ return x; }
	float getY(){ return y; }
	float getTime(){ return time; }
	void update();
	~PointSprite();
private:
	float x, y, hspeed = 0, vspeed = 0, time;
	std::string texture;
};
#endif