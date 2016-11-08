#include "core/Graphics.h"
#include <exception>
#include <string>
#include <memory>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>
#include "core/Logger.h"
#include "core/Input.h"
#include "core/Engine.h"

#define TAG "Graphics"

namespace Graphics
{
	namespace
	{
		GLFWwindow* window;
		NVGcontext* vg;
	}

	void resizeCallback(GLFWwindow* window, int width, int height)
	{
		Engine::resize(width, height);
	}

	void init(std::string name, int w, int h)
	{
		Logger::info(TAG, "Initializing graphics");

		if (!glfwInit())
			throw std::runtime_error("Failed to initialize GLFW.");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

		glfwWindowHint(GLFW_SAMPLES, 0);
		glfwWindowHint(GLFW_RED_BITS, 8);
		glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8);
		glfwWindowHint(GLFW_ALPHA_BITS, 8);
		glfwWindowHint(GLFW_STENCIL_BITS, 8);
		glfwWindowHint(GLFW_DEPTH_BITS, 24);

		window = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);

		if (!window)
			throw std::runtime_error("Failed to create window.");

		Input::init(window);

		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

		glfwSetFramebufferSizeCallback(window, resizeCallback);

		vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
	}

	void destroy()
	{
		Logger::info(TAG, "Destroying graphics");
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void update()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	int getWidth()
	{
		int w;
		glfwGetFramebufferSize(window, &w, NULL);
		return w;
	}

	int getHeight()
	{
		int h;
		glfwGetFramebufferSize(window, NULL, &h);
		return h;
	}

	float getPixelRatio()
	{
		int fw, ww;
		glfwGetFramebufferSize(window, &fw, NULL);
		glfwGetWindowSize(window, &ww, NULL);
		return (float) fw / (float) ww;
	}

	NVGcontext* nvg()
	{
		return vg;
	}
}
