#define GLEW_STATIC
#define GLM_FORCE_RADIANS

#include "Renderer.h"
GLFWwindow* window;

int main()
{

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int w = 1024;
	int h = 768;
	window = glfwCreateWindow(w, h,
		"Cyborg-Engine", NULL, NULL);
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Renderer::FramebufferSizeCallback);
	Renderer::FramebufferSizeCallback(window, w, h);
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	Renderer::initRender(window);

	float a = 0;

	do{
		a += 0.01;
		//render stuff
		Renderer::initDraw();
		Renderer::setColor(1, 0.5, 0, 1);
		Renderer::drawTriangle(sin(a), cos(a), -sin(a*7), -cos(a*7), sin(a), -cos(a*20));
		Renderer::drawTriangle(-sin(a), -cos(a), sin(a*7), cos(a*7), -sin(a), cos(a*20));
		Renderer::setColor(0, abs(cos(a * 10)), abs(cos(a * 13)), 1);
		Renderer::drawRectangle(-0.75, -0.75, 0.75, 0.75);
		Renderer::setColor(1, 1, 0, 1);
		Renderer::drawPie(-0.5, 0, 0.5, 1-(abs(cos(a*16))/ 8));
		Renderer::drawMultiColorTriangle(-0.25,-0.25,0.25,-0.25,0.25,0.25);
		Renderer::setColor(1.0,0.0,0.0,1.0);
		Renderer::drawLine(sin(a),cos(a),-sin(a),-cos(a),5.0);
		Renderer::render();
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);


	Renderer::uninitRender();
	glfwTerminate();
	return 0;
}