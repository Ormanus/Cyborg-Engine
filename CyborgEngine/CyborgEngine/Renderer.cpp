#include "Renderer.h"
#include "common\shader.hpp"

namespace {
	GLuint programID;
	GLuint vertexbuffer;
	GLuint VertexArrayID;
	GLuint indexbuffer;
	GLFWwindow* window;
	glm::mat4 MVP(1.0);
	GLuint MVP_MatrixID;
	GLuint TextureID;
	GLuint uvbuffer;
	GLuint colorbuffer;
	GLuint Texture;
	glm::mat4 VP;
	glm::vec4 DefaultColor;
};

void Renderer::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Renderer::initDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Tyhjennet��n ruutu
	// Koordinaatisto / Viewport
	glm::vec3 x_axis(1.0, 0.0, 0.0);
	glm::vec3 y_axis(0.0, 1.0, 0.0);
	glm::vec3 z_axis(0.0, 0.0, 1.0);

	glm::vec3 cam_pos(0, 0, 0);
	glm::vec3 cam_up = y_axis;
	glm::vec3 cam_right = x_axis;
	glm::vec3 cam_front = -z_axis; //oikeakatinen koordinaatisto
	glm::mat4 P = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glm::mat4 V = glm::ortho(-1.0f, 1.0f, -1.0f*height / width, 1.0f*height / width);
	VP = V*P;

	glUseProgram(programID);
	// ---------------------------
}


void Renderer::render()
{
	glfwSwapBuffers(window);
}

void Renderer::initRender(GLFWwindow* w)
{
	window = w;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Taustav�ri - musta

	//asetetaan piirtov�ri oranssiksi
	DefaultColor.r = 1.0f;
	DefaultColor.g = 0.4f;
	DefaultColor.b = 0.0f;
	DefaultColor.a = 1.0f;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//Ladataan shaderit
	//valmiissa ohjelmassa bool setShaders() -funktio ajonaikaiseen shaderien vaihtoon?
	programID = LoadShaders("shaders/VertexShader.vertexshader", "shaders/FragmentShader.fragmentshader");
	//----------------

	//luodaan v�ribufferi. 
	//TODO: siirr� muualle my�hemmin?

	static const GLfloat g_color_buffer_data[] = {
		DefaultColor.r, DefaultColor.g, DefaultColor.b,
		DefaultColor.r, DefaultColor.g, DefaultColor.b,
		DefaultColor.r, DefaultColor.g, DefaultColor.b,
	};

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(g_color_buffer_data),
		g_color_buffer_data, GL_STATIC_DRAW);

	//glEnable(jotain)
	//glEnable(GL_BLEND);
	//glBlendEquation(GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::uninitRender()
{
	// ???
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &indexbuffer);
}

void Renderer::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	//piirr� kolmio:
	//Toimii toistaiseksi. Optimointi edelleen kesken.
	//T�ll� hetkell� todenn�k�isesti hidas, mutta ei kuitenkaan vuoda liikaa muistia...

	static const GLfloat g_vertex_buffer_data[] = {
		x1, y1, 1.0f,
		x2, y2, 1.0f,
		x3, y3, 1.0f,
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	static const GLubyte g_indices[] =
	{
		0, 1, 2,
	};
	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_STATIC_DRAW);

	MVP_MatrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(MVP_MatrixID, 1, GL_FALSE, &MVP[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 1
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &indexbuffer);
}
