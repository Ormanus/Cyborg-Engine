#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <unordered_map>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <fstream>
#include <SOIL.h>


class TextureManager
{
public:
	GLuint getTexture(const std::string name);
	void loadTexture(std::string name, std::string filePath);
	TextureManager();
	~TextureManager();
private:

	 std::vector<unsigned char> png;
	 unsigned char* image;
	 int width, height;

	 GLuint texture;
	 std::unordered_map<std::string, GLuint> textures;
	 void deleteTexture(std::string name);

	
};

#endif