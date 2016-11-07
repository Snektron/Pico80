#include "core/gl/Shader.h"
#include <string>
#include <fstream>
#include <streambuf>
#include "glad/glad.h"
#include "core/Logger.h"

#define TAG "Shader"

namespace Shader
{
	ShaderProgram::ShaderProgram(GLuint program):
			program(program)
	{
		if (!program)
			throw std::runtime_error("Invalid shader.");
	}

	void ShaderProgram::bind()
	{
		glUseProgram(program);
	}

	void ShaderProgram::release()
	{
		glUseProgram(0);
	}

	GLuint ShaderProgram::getUniformLocation(std::string name)
	{
		auto uniform = uniforms.find(name);
		if (uniform == uniforms.end())
		{
			GLuint location = glGetUniformLocation(program, name.c_str());
			uniforms[name] = location;
			return location;
		}
		return uniform->second;
	}

	GLuint ShaderProgram::getAttribLocation(std::string name)
	{
		auto attrib = attributes.find(name);
		if (attrib == attributes.end())
		{
			GLuint location = glGetAttribLocation(program, name.c_str());
			attributes[name] = location;
			return location;
		}
		return attrib->second;
	}

	void ShaderProgram::vertexAttribPointer(std::string name, GLuint size, GLuint type, GLuint normalize, GLsizei stride, const void *data)
	{
		glVertexAttribPointer(getAttribLocation(name), size, type, normalize, stride, data);
	}

	void ShaderProgram::enableVertexAttrib(std::string name)
	{
		glEnableVertexAttribArray(getAttribLocation(name));
	}

	void ShaderProgram::disableVertexAttrib(std::string name)
	{
		glDisableVertexAttribArray(getAttribLocation(name));
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(program);
	}

	Builder& Builder::withFile(GLuint type, std::string path)
	{
		std::ifstream input(path);
		if (!input)
			throw std::runtime_error("Failed to open shader file " + path);

		std::string source((std::istreambuf_iterator<char>(input)),
						std::istreambuf_iterator<char>());
		return withShader(type, source);
	}

	Builder& Builder::withShader(GLuint type, std::string source)
	{
		const char *src = source.c_str();
		int length = source.length();
		int status = GL_TRUE;

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

	Program Builder::build()
	{
		int status = GL_TRUE;
		GLuint program(glCreateProgram());

		if (!program)
			throw std::runtime_error("Failed to create shader program.");

		for (auto i = shaders.begin(); i != shaders.end(); i++)
			glAttachShader(program, *i);

		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &status);

		for (auto i = shaders.begin(); i != shaders.end(); i++)
		{
			glDetachShader(program, *i);
			glDeleteShader(*i);
		}

		if (status == GL_FALSE)
			throw std::runtime_error("Failed to link program:\n" + getProgramInfoLog(program));

		glValidateProgram(program);
		glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
		if (status == GL_FALSE)
			throw std::runtime_error("Failed to validate program:\n" + getProgramInfoLog(program));

		return std::make_shared<ShaderProgram>(program);
	}

	std::string Builder::getShaderInfoLog(GLuint shader)
	{
		GLsizei length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string log = std::string(length, 0);
		glGetShaderInfoLog(shader, length, &length, &log[0]);
		return log;
	}

	std::string Builder::getProgramInfoLog(GLuint program)
	{
		GLsizei length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		std::string log = std::string(length, 0);
		glGetProgramInfoLog(program, length, &length, &log[0]);
		return log;
	}
}
