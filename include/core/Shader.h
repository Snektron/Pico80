#ifndef INCLUDE_CORE_SHADER_H_
#define INCLUDE_CORE_SHADER_H_

#include <string>
#include <memory>
#include <vector>
#include "glad/glad.h"

class Shader
{
private:
	GLuint program;

public:
	Shader(GLuint program);
	~Shader();
};

class ShaderBuilder
{
private:
	std::vector<GLuint> shaders;

public:
	ShaderBuilder& withShaderFile(GLuint type, std::string file);
	ShaderBuilder& withShaderSource(GLuint type, std::string source);
	std::shared_ptr<Shader> build();
};

#endif /* INCLUDE_CORE_SHADER_H_ */
