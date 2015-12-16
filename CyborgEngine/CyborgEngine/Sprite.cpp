#include "Sprite.h"

namespace
{
	Sprite*SP;
};

Sprite::Sprite(float r, float c, std::string t)
{
	rows = r;
	columns = c;
	texture = t;
	setSprite(rows, columns);
}


Sprite::~Sprite()
{
	coordinates.clear();
}

void Sprite::setSprite(float rows, float columns)
{

	float spriteW = SP->getSpriteWidth(rows);
	float spriteH = SP->getSpriteHeight(columns);
	std::cout << spriteW << ", " << spriteH << std::endl;
	int numberPerRow = 1 / spriteW;
	int size = rows*columns;
	std::cout << numberPerRow << std::endl;

	for (int i = 1; i < size; i++)
	{
		float tX = (i%numberPerRow)*spriteW;
		float tY = (i / numberPerRow + 1)*spriteH;
		glm::vec2 spriteCoords = { tX, tY };
		coordinates.insert(std::make_pair(i, spriteCoords));
	}

}
glm::vec2 Sprite::getSprite(int a)
{
	auto i = coordinates.find(a);
	if (i == coordinates.end())
	{
		std::cout << "Allah" << std::endl;
		return glm::vec2(0, 0);
	}
	else
	{
		return i->second;
	}
}
