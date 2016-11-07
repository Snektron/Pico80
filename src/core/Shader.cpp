#include "core/gfx/Shader.h"
#include <string>
#include <fstream>
#include "glad/glad.h"
#include "core/Logger.h"

#define TAG "Shader"

namespace Shader
{
	Builder& Builder::withShader(GLuint type, std::string source)
	{
		const char *src = source.c_str();
		int length = source.length();
		int status = 0;

		GLuint shader(glCreateShader(type));
		if (!shader)
			throw std::runtime_error("Failed to create shader.");

		glShaderSource(shader, 1, &src, &length);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
			throw std::runtime_error("Failed to compile shader:\n" + getShaderInfoLog(shader));

		shaders.push_back(shader);

		return *this;
	}

	GLuint Builder::build()
	{
		int status;
		GLuint program(glCreateProgram());

		if (!program)
			throw std::runtime_error("Failed to create shader program.");

		for (auto i = shaders.begin(); i != shaders.end(); i++)
			glAttachShader(program, *i);

		glLinkProgram(program);
		glGetProgramiv(program, GL_COMPILE_STATUS, &status);

		for (auto i = shaders.begin(); i != shaders.end(); i++)
		{
			glDetachShader(program, *i);
			glDeleteShader(*i);
		}

		if (status == GL_FALSE)
			throw std::runtime_error("Failed to link shader:\n" + getProgramInfoLog(program));

		glValidateProgram(program);
		glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
		if (status == GL_FALSE)
			throw std::runtime_error("Failed to validate shader:\n" + getProgramInfoLog(program));

		return program;
	}

	std::string getShaderInfoLog(GLuint shader)
	{
		GLsizei length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string log = std::string(length, 0);
		glGetShaderInfoLog(shader, length, &length, &log[0]);
		return log;
	}

	std::string getProgramInfoLog(GLuint program)
	{
		GLsizei length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		std::string log = std::string(length, 0);
		glGetProgramInfoLog(program, length, &length, &log[0]);
		return log;
	}
}
