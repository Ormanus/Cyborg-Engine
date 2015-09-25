#include "TextureManager.h"


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

	const char* c = filePath.c_str();
	//Ladataan tekstuuri. Suora linkki sijaintiin esim. "images/image.bmp"
	texture = loadBMP_custom(c);

	GLuint id;
	id = textures.size();
	//Luodaan openGL tekstuuri
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(id, 0);

	//Asetetaan tekstuuri unordered_mappiin, 
	//annetaan sille nimi jolla sit‰ voi hakea
	textures.insert(make_pair(name, id));
}

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