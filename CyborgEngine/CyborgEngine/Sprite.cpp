#include "Sprite.h"


Sprite::Sprite(int tW, int tH, int sW, int sH)
{
	tW = texWidth;
	tH = texHeight;
	sW = spriteWidth;
	sH = spriteHeight;
}


Sprite::~Sprite()
{
}
void Sprite::setSpriteSheet(float posX, float posY, int frameIndex)
{
	const float verts[] =
	{
		posX, posY,
		posX + spriteWidth, posY,
		posX + spriteWidth, posY + spriteHeight,
		posX, posY + spriteHeight
	};

	const float tw = float(spriteWidth) / texWidth;
	const float th = float(spriteHeight) / texHeight;
	const int numPerRow = texWidth / spriteWidth;
	const float tx = (frameIndex % numPerRow) * tw;
	const float ty = (frameIndex / numPerRow + 1) * th;
	const float texVerts[] =
	{
		tx, ty,
		tx + tw, ty,
		tx + tw, ty + th,
		tx, ty + th
	};
}
