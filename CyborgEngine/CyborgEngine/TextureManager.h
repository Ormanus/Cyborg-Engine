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

namespace
{
	GLuint texture;
	GLuint loadBMP_custom(const char* filepath);
}


class TextureManager
{
public:

	GLuint getTexture(std::string name);
	TextureManager();
	~TextureManager();
private:

	std::unordered_map<std::string, GLuint> textures;
	void loadTexture(std::string name, std::string filePath);
	void deleteTexture(std::string name);

	
};

#endif