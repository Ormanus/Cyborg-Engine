#include "TextureManager.h"
#include "texture.hpp"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	// Tyhjennet‰‰n textures array.
	//glDeleteTextures(textures.size(), textures);
	textures.clear();
}

void TextureManager::loadTexture(std::string name, std::string filePath)
{

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//ladataan kuva tiedostosta (PNG, BMP, JPG, TGA, DDS, PSD, HDR)
	const char* c = filePath.c_str();
	unsigned char* image = SOIL_load_image(c, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == NULL)            // Throw error if load fails
		std::cout << "Could not load image \"" + name + "\"\n" + SOIL_last_result();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//luodaan tekstuuri

	std::cout << "image:\n" << image;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	textures.insert(make_pair(name, texture));
	SOIL_free_image_data(image);

	std::cout << "Loaded texture: " << name << std::endl;
	//Vapautetaan muistista k‰ytˆn j‰lkeen
}



//void TextureManager::loadTexture(std::string name, std::string filePath)
//{
//	//ladataan kuva tiedostosta (PNG, BMP, JPG, TGA, DDS, PSD, HDR)
//	const char* c = filePath.c_str();
//	GLuint texture = loadBMP_custom(c);//SOIL_load_OGL_texture(c, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
//	textures.insert(make_pair(name, texture));
//
//	std::cout << "Loaded texture: " << name << std::endl;
//	//Vapautetaan muistista k‰ytˆn j‰lkeen
//}

void TextureManager::deleteTexture(std::string name)
{
	auto i = textures.find(name);

	if (i == textures.end())
	{
		std::cout << "Texture with this name doesn't exist." << std::endl;
		return;
	}

	GLuint id = i->second;
	//poistetaan openGL texture t‰ss‰
	glDeleteTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, NULL);

	textures.erase(i);
}

GLuint TextureManager::getTexture(std::string name)
{
	auto i = textures.find(name);

	if (i == textures.end())
	{
		std::cout << "Texture with this name doesn't exist." << std::endl;
		return 0;
	}

	return i->second;

}