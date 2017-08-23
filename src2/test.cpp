#include <iostream>
#include <string>
#include <cstdint>
#include <cmath>
#include "../src/deps/Program.hpp"
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	std::cout << "Window resized to " << width << " by " << height << '\n';
	glViewport(0,0,width,height);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800,800,"Learn OpenGL",NULL,NULL);
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
	if (window == NULL)
	{
		std::cout << "You done fucked up.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glViewport(0,0,800,800);
	Program program;
}
