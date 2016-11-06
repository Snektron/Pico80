#include "core/Shader.h"
#include <cstring>
#include <fstream>
#include "glad/glad.h"

Shader::Shader(GLuint program):
	program(program)
{}

Shader::~Shader()
{
	glDeleteProgram(program);
}

ShaderBuilder& ShaderBuilder::withShaderFile(GLuint type, std::string file)
{
	std::ifstream input(file);
	if (!input)
		throw std::runtime_error("Failed to open shader: " + file);

	std::string str((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
	return withShaderSource(type, str);
}

ShaderBuilder& ShaderBuilder::withShaderSource(GLuint type, std::string source)
{
	GLuint shader = glCreateShader(type);
	if (!shader)
		throw std::runtime_error("Failed to create shader.");

	const char *src = source.c_str();
	int length = source.length();
	glShaderSource(shader, 1, &src, &length);
	glCompileShader(shader);

	int status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLsizei length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string log = std::string(length, 0);
		glGetShaderInfoLog(shader, length, &length, &log[0]);
		throw std::runtime_error("Failed to compile shader: \n" + log);
	}

	shaders.push_back(shader);
	return *this;
}

std::shared_ptr<Shader> ShaderBuilder::build()
{
	GLuint program(glCreateProgram());

	if (!program)
		throw std::runtime_error("Failed to create shader program.");

	for (auto i = shaders.begin(); i != shaders.end(); i++)
		glAttachShader(program, *i);

	glLinkProgram(program);
	int status;
	glGetProgramiv(program, GL_COMPILE_STATUS, &status);

	for (auto i = shaders.begin(); i != shaders.end(); i++)
	{
		glDetachShader(program, *i);
		glDeleteShader(*i);
	}

	if (status == GL_FALSE)
		throw std::runtime_error("Failed to link shader.");

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
		throw std::runtime_error("Failed to validate shader.");

	return std::make_shared<Shader>(program);
}
