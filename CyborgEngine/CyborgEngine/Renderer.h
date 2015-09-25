#ifndef RENDERER_H
#define RENDERER_H

#include "TextureManager.h"





class Renderer
{
public:

	void static render();
	void static initRender(GLFWwindow* w);
	void static uninitRender();
	void static initDraw();
	void static FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	Renderer();
	~Renderer();
};



#endif