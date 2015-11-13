#include "Polygon.h"
#include "Renderer.h"

Polygon::Polygon()
{
	setRotation(0);
	setOrigin(0, 0);
}

Polygon::~Polygon()
{
	//how do I garbage collect?
}

void Polygon::setPoints(glm::vec2* p, int size)
{
	//float maxX = 0, maxY = 0, minX = 0, minY = 0;
	points = new glm::vec2[size];
	numPoints = 0;
	points[0] = glm::vec2(0, 0);
	for (int i = 0; i < size; i++)
	{
		points[numPoints+1] = p[i];
		numPoints++;
		if (p[i].x > maxX){ maxX = p[i].x; }
		if (p[i].y > maxY){ maxY = p[i].y; }
		if (p[i].x < minX){ minX = p[i].x; }
		if (p[i].y < minY){ minY = p[i].y; }
		points[0].x += p[i].x;
		points[0].y += p[i].y;
	}

	points[0].x /= size;
	points[0].y /= size;
}