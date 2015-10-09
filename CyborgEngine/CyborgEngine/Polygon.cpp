#include "Polygon.h"
#include "Renderer.h"

Polygon::Polygon()
{
	setRotation(0);
	setOrigin(0, 0);
}

Polygon::~Polygon()
{
}

void Polygon::setPoints(glm::vec2* p, int number)
{
	float maxX = 0, maxY = 0, minX = 0, minY = 0;
	points.clear();
	points.push_back(glm::vec2(0, 0)); //center
	for (int i = 0; i < number; i++)
	{
		points.push_back(p[i]);
		if (p[i].x > maxX){ maxX = p[i].x; }
		if (p[i].y > maxY){ maxY = p[i].y; }
		if (p[i].x < minX){ minX = p[i].x; }
		if (p[i].y < minY){ minY = p[i].y; }
	}
	points[0].x = (maxX + minX) / 2;
	points[0].y = (maxY + minY) / 2;
}

std::vector<glm::vec2>* Polygon::getPoints()
{
	rotatedPoints.clear();
	//TODO: rotation matrix
	for (auto point : points)
	{
		float dx = (point.x - origin.x);
		float dy = (point.y - origin.y);
		float l = sqrt(dx*dx + dy*dy);
		float d = atan2(dy, dx) + rotation;
		glm::vec2 temp(origin.x + cos(d)*l, origin.y + sin(d)*l);
		rotatedPoints.push_back(temp);
	}
	return &rotatedPoints;
}