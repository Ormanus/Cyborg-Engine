#include "Renderer.h"
#include "Camera.h"

static GLFWwindow* window = nullptr;

namespace
{

	glm::mat4 VP;
};

glm::vec3 x_axis(1.0, 0.0, 0.0);
glm::vec3 y_axis(0.0, 1.0, 0.0);
glm::vec3 z_axis(0.0, 0.0, 1.0);
glm::vec3 cam_pos(0, 0, 0);
glm::vec3 cam_up = y_axis;
glm::vec3 cam_right = x_axis;
glm::vec3 cam_front = -z_axis; //oikeakatinen koordinaatisto
bool keys[1024];

void Camera::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	float scale = width / height;
	glViewport(0, 0, width / scale, height);
}


void Camera::Draw()
{

	//int width, height;
	//glfwGetFramebufferSize(window, &width, &height);
	//glm::mat4 V = glm::ortho(-1.0f, 1.0f, -1.0f*height / width, 1.0f*height / width);
	//glm::mat4 P = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);
	//VP = V*P;
	//glm::mat4 view;
	//view = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);
}

glm::mat4 Camera::getMVP()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f*height / width, 1.0f*height / width);
	glm::mat4 view = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);
	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 mvp = projection * view * model;
	return mvp;
}

//kutsutaan aina kun näppäintä painetaan/vapautetaan.
void Camera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

//Kameran kontrollit
void Camera::do_movement()
{
	GLfloat cam_speed = 0.1f;
	if (keys[GLFW_KEY_W])
		cam_pos += cam_speed * cam_front;
	if (keys[GLFW_KEY_S])
		cam_pos -= cam_speed * cam_front;
	if (keys[GLFW_KEY_A])
		cam_pos -= glm::normalize(glm::cross(cam_front, cam_up)) * cam_speed;
	if (keys[GLFW_KEY_D])
		cam_pos += glm::normalize(glm::cross(cam_front, cam_up)) * cam_speed;
}