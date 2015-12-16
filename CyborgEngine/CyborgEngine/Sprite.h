#ifndef Sprite_H
#define Sprite_H
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <string>
#include <iostream>

class Sprite
{

public:

	Sprite(float r, float c, std::string t);
	~Sprite();

	float getSpriteWidth(float a){ return  (1.0 / a); }
	float getSpriteHeight(float b){ return (1.0 / b); }
	std::string getTexture(){ return texture; }
	void setSprite(float rows, float columns);
	glm::vec2 getSprite(int a);

	float rows, columns;
	std::string texture;
	std::unordered_map<int, glm::vec2> coordinates;
	float getSpriteWidth(int rows){ return  1.0 / rows; }
	float getSpriteHeight(int columns){ return 1.0 / columns; }


};

#endif;