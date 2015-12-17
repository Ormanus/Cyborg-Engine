#ifndef CAMERA_H
#define CAMERA_H
#include "glm\glm.hpp"



class Camera
{

	public:

		void static key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		void static do_movement();
		void static Draw();
		void static FramebufferSizeCallback(GLFWwindow* window, int width, int height);
		glm::mat4 static getMVP();

		Camera(GLFWwindow* w){ window = w; };
		~Camera(){};

	private:
		
		static GLFWwindow* window;


};
#endif