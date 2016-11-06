#include "core/Graphics.h"
#include <exception>
#include <string>
#include <memory>
#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include "core/Logger.h"
#include "core/Display.h"
#include "core/Input.h"

#define TAG "Graphics"

namespace
{
	GLFWwindow* window;
}

void Graphics::init(std::string name, int w, int h)
{
	Logger::info(TAG, "Initializing graphics");

	if (!glfwInit())
		throw std::runtime_error("Failed to initialize GLFW.");

	window = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);

	if (!window)
		throw std::runtime_error("Failed to create window.");

	Input::init(window);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

	glViewport(0, 0, w, h);
}

void Graphics::destroy()
{
	Logger::info(TAG, "Destroying graphics");
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Graphics::update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

int Graphics::get_width()
{
	int w;
	glfwGetFramebufferSize(window, NULL, &w);
	return w;
}

int Graphics::get_height()
{
	int h;
	glfwGetFramebufferSize(window, &h, NULL);
	return h;
}
