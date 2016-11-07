#include "core/gl/Buffer.h"
#include "glad/glad.h"

namespace Buffer
{
	VBO::VBO()
	{
		glGenBuffers(1, &vbo);
	}

	GLuint VBO::getId()
	{
		return vbo;
	}

	void VBO::bind(GLuint location)
	{
		glBindBuffer(location, vbo);
	}

	void VBO::data(GLuint location, GLuint elements, float* vertices, GLuint type)
	{
		glBufferData(location, elements, vertices, type);
	}

	VBO::~VBO()
	{
		glDeleteBuffers(1, &vbo);
	}


	VAO::VAO()
	{
		glGenVertexArrays(1, &vao);
	}

	GLuint VAO::getId()
	{
		return vao;
	}

	void VAO::bind()
	{
		glBindVertexArray(vao);
	}

	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &vao);
	}
}
