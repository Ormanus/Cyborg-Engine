#include "Sprite.h"



Sprite::Sprite()
{
	rows = 0;
	columns = 0;
	setSprite();
}


Sprite::~Sprite()
{
	coordinates.clear();
}

void Sprite::setSprite()
{

	float spriteW = getSpriteWidth();
	float spriteH = getSpriteHeight();
	int size = rows*columns;
	/*std::cout << numberPerRow << std::endl;*/
	for (int i = 1; i < size; i++)
	{
		float tX = (i%rows)*spriteW;
		float tY = (i / rows + 1)*spriteH;
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
