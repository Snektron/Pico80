#ifndef INCLUDE_CORE_GFX_SHADER_H_
#define INCLUDE_CORE_GFX_SHADER_H_

#include <string>
#include <vector>
#include "glad/glad.h"

namespace Shader
{
	class Program
	{

	};

	class Builder
	{
	private:
		std::vector<int> shaders;

	public:
		Builder& withShader(GLuint type, std::string source);
		GLuint build();

	private:
		std::string getShaderInfoLog(GLuint shader);
		std::string getProgramInfoLog(GLuint program);
	};
}
#endif /* INCLUDE_CORE_GFX_SHADER_H_ */
