#include "Renderer.h"

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
	GLuint Texture;
	glm::mat4 VP;
	glm::vec4 DefaultColor;
};

void Renderer::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Renderer::initDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Tyhjennetään ruutu
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
	// ---------------------------
}


void Renderer::render()
{
	glfwSwapBuffers(window);
}

void Renderer::initRender(GLFWwindow* w)
{
	window = w;
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f); // Taustaväri - musta

	//aseta piirtoväri valkoiseksi
	DefaultColor.r = 1.0f;
	DefaultColor.g = 1.0f;
	DefaultColor.b = 1.0f;
	DefaultColor.a = 1.0f;

	//Ladataan shaderit
		//shader
	//----------------

	//glEnable(jotain)
	//glEnable(GL_BLEND);
	//glBlendEquation(GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::uninitRender()
{
	// ???
}

void Renderer::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	glLoadIdentity();
	glBegin(GL_TRIANGLES);

	glColor3f(DefaultColor.r, DefaultColor.g, DefaultColor.b);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertex3f(x1, y1, 0.0f);
	glVertex3f(x2, y2, 0.0f);
	glVertex3f(x3, y3, 0.0f);

	glEnd();

	glfwSwapBuffers(window);

	/*  ### Nämä otetaan käytöön vasta shaderien kanssa? ###

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
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                  // 
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	*/
}
