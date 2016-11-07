#ifndef INCLUDE_CORE_GFX_SHADER_H_
#define INCLUDE_CORE_GFX_SHADER_H_

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "glad/glad.h"

namespace Shader
{
	class ShaderProgram
	{
	private:
		GLuint program;
		std::map<std::string, GLuint> uniforms;
		std::map<std::string, GLuint> attributes;

	public:
		ShaderProgram(GLuint program);

		void bind();
		void release();

		GLuint getUniformLocation(std::string name);
		GLuint getAttribLocation(std::string name);

		void vertexAttribPointer(std::string name, GLuint size, GLuint type, GLuint normalize, GLsizei stride, const void* data);
		void enableVertexAttrib(std::string name);
		void disableVertexAttrib(std::string name);

		~ShaderProgram();
	};

	typedef std::shared_ptr<ShaderProgram> Program;

	class Builder
	{
	private:
		std::vector<int> shaders;

	public:
		Builder& withFile(GLuint type, std::string path);
		Builder& withShader(GLuint type, std::string source);
		Program build();

	private:
		std::string getShaderInfoLog(GLuint shader);
		std::string getProgramInfoLog(GLuint program);
	};
}
#endif /* INCLUDE_CORE_GFX_SHADER_H_ */
