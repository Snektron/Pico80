#ifndef INCLUDE_CORE_DISPLAY_H_
#define INCLUDE_CORE_DISPLAY_H_

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 128
#define DISPLAY_INDEX(x, y) (DISPLAY_WIDTH * (y & 0x7F) + (x & 0x7F))

#include <cstdint>
#include <eigen3/Eigen/Core>
#include "glad/glad.h"
#include "core/gl/Shader.h"

#define COLOR(r, g, b) {r, g, b, 0xFF}

typedef union
{
	struct { uint8_t r, g, b, a; };
	uint32_t rgba;
} color_t;

class Display
{
private:
	GLuint texture;
	color_t pixels[DISPLAY_WIDTH * DISPLAY_HEIGHT];
	Shader::Program shader;
	GLuint vbo;
	int renderWidth, renderHeight;

public:
	Display();
	void render(Eigen::Matrix4f& mv, Eigen::Matrix4f& p);
	void resize(int width, int height);
	void write(uint8_t *data);
	~Display();
};

#endif /* INCLUDE_CORE_DISPLAY_H_ */
