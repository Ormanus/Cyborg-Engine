#include "TextureManager.h"


TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	// Tyhjennet��n textures array.
	//glDeleteTextures(textures.size(), textures);
	textures.clear();
}

void TextureManager::loadTexture(std::string name, std::string filePath)
{
	//ladataan kuva tiedostosta (PNG, BMP, JPG, TGA, DDS, PSD, HDR)
	const char* c = filePath.c_str();
	image = SOIL_load_image(c, &width, &height, 0, SOIL_LOAD_RGBA);
	//luodaan tekstuuri
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	//Vapautetaan muistista k�yt�n j�lkeen
	SOIL_free_image_data(image); 


	
	glEnable(GL_TEXTURE_2D);
	GLuint id;
	id = textures.size();
	//Luodaan openGL tekstuuri --------------------
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(id, 0);
	//Ehk� voisi toteuttaa vasta siell� miss� kutsutaan tekstuuria?

	//Asetetaan tekstuuri unordered_mappiin, 
	//annetaan sille nimi jolla sit� voi hakea
	textures.insert(make_pair(name, id));

	std::cout << "Loaded texture: " << name << std::endl;

	
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
	//poistetaan openGL texture t�ss�
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