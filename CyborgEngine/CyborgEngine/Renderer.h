#ifndef RENDERER_H
#define RENDERER_H

//tarvitaankko n‰it‰ kaikkia?
//TODO: poista ylim‰‰r‰iset, siirr‰ osa .cpp-tiedostoon
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Polygon.h"
#include "TextureManager.h"

class Renderer
{
public:

	void static render();
	void static initRender(GLFWwindow* w);
	void static uninitRender();
	void static initDraw();
	void static FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	void static drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
	void static drawTexturedTriangle(float x1, float y1, float x2, float y2, float x3, float y3, std::string texture);
	void static drawRectangle(float x1, float y1, float x2, float y2);
	void static drawCircle(float x, float y, float r);
	void static drawPie(float x, float y, float r, float percentage);
	void static drawPolygon(Polygon* p, const float x, const float y);
	void static drawPolygonTextured(Polygon* p, const float x, const float y, std::string textureName);

	void static setColor(float r, float g, float b, float a);

	Renderer(){}
	~Renderer(){}
};



#endif