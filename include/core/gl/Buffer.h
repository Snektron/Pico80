#ifndef INCLUDE_CORE_GL_BUFFER_H_
#define INCLUDE_CORE_GL_BUFFER_H_

#include "glad/glad.h"

namespace Buffer
{
	class VBO
	{
	private:
		GLuint vbo;
	public:
		VBO();
		GLuint getId();
		void bind(GLuint location);
		void data(GLuint location, GLuint elements, float* vertices, GLuint type);
		~VBO();
	};

	class VAO
	{
	private:
		GLuint vao;
	public:
		VAO();
		GLuint getId();
		void bind();
		~VAO();
	};
}

#endif /* INCLUDE_CORE_GL_BUFFER_H_ */
