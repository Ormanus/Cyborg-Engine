#ifndef RENDERER_H
#define RENDERER_H

#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>





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