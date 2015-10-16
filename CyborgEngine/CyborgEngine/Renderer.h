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
	enum Colors
	{
		CRed=		0xFF0000,
		CGreen=		0xFF0000,
		CBlue=		0x0000FF,
		CYellow=	0xFFFF00,
		CMagneta=	0xFF00FF,
		CCyan=		0x00FFFF,
		COrange=	0xFF8000,
		CBlack=		0x000000,
		CWhite=		0xFFFFFF,
		CGray=		0x808080,
	};

	void static render();
	void static initRender(GLFWwindow* w);
	void static uninitRender();
	void static initDraw();
	void static FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	void static drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
	void static drawRectangle(float x1, float y1, float x2, float y2);
	void static drawCircle(float x, float y, float r);
	void static drawPie(float x, float y, float r, float percentage);
	void static drawMultiColorTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
	void static drawLine(float startPointX, float startPointY, float endPointX, float endPointY,float width);
	void static setColor(float r, float g, float b, float a);
	void static setColor(int color);
	

	Renderer(){}
	~Renderer(){}
};



#endif