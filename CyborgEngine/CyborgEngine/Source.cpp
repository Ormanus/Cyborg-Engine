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

	//int w = 1024;
	int w = 768;
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

	

	Polygon p;
	glm::vec2 points[]
	{
		
		glm::vec2(0.0, 0.21),
		glm::vec2(0.05, 0.05),
		glm::vec2(0.4, 0.0),
		glm::vec2(0.05, -0.05),
		glm::vec2(0.0, -0.21),
		glm::vec2(-0.05, -0.05),
		glm::vec2(-0.4, 0.0),
		glm::vec2(-0.05, 0.05),
	};
	p.setPoints(points, 8);
	p.setOrigin(-0.5, 0.0);

	do{
		a += 0.01;
		//clear screen
		Renderer::initDraw();
		//draw
		

		for (int i = 0; i < 8; i++)
		{

			Renderer::setColor(0, 1, (float)i/8, 1);
			p.setRotation(a+i*3.14159265/4);
			Renderer::drawPolygonTextured(&p, 0, 0, "testi");

		}

		//Renderer::drawTexturedTriangle(0.5, 1.0, 0.0, 0.5, -1.0, 0.0, "testi");

		//swap buffers
		Renderer::render();
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);


	Renderer::uninitRender();
	glfwTerminate();
	return 0;
}