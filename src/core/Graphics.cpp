#include "core/Graphics.h"
#include <exception>
#include <string>
#include <memory>
#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include "core/Logger.h"
#include "core/Input.h"
#include "core/Engine.h"

#define TAG "Graphics"

namespace
{
	GLFWwindow* window;
}

void resizeCallback(GLFWwindow* window, int width, int height)
{
	Engine::resize(width, height);
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

	glfwSetFramebufferSizeCallback(window, resizeCallback);
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

int Graphics::getWidth()
{
	int w;
	glfwGetFramebufferSize(window, &w, NULL);
	return w;
}

int Graphics::getHeight()
{
	int h;
	glfwGetFramebufferSize(window, NULL, &h);
	return h;
}
