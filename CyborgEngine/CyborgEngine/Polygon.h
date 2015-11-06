#ifndef POLYGON_H
#define POLYGON_H

#include "glm\glm.hpp"
#include <vector>

class Polygon
{
public:
	Polygon();
	~Polygon();

	//get
	glm::vec2 getOrigin()const{ return origin; }
	float getRotation()const{ return rotation; }
	std::vector<glm::vec2>* getPoints();
	glm::vec2 getMin(){ return glm::vec2(minX, minY); }
	glm::vec2 getMax(){ return glm::vec2(maxX, maxY); }

	//set
	void setOrigin(glm::vec2 newOrigin){ origin = newOrigin; }
	void setOrigin(float x, float y){ origin.x = x; origin.y = y; }
	void setRotation(float angle){ rotation = angle; }
	void setPoints(glm::vec2* p, int size);
private:
	std::vector<glm::vec2> points;
	std::vector<glm::vec2> rotatedPoints;
	float maxX = 0, maxY = 0, minX = 0, minY = 0;
	glm::vec2 origin;
	float rotation;
};

#endif