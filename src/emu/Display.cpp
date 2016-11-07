#include "emu/Display.h"
#include <algorithm>
#include <memory>
#include <cstdint>
#include <eigen3/Eigen/Core>
#include "glad/glad.h"
#include "core/Graphics.h"
#include "core/Logger.h"
#include "core/gl/Shader.h"

#define TAG "Display"

const color_t palette[16] =
{
	COLOR( 20,  12,  28), // 0 black
	COLOR( 68,  36,  52), // 1 plum
	COLOR( 48,  52, 109), // 2 midnight
	COLOR( 78,  74,  78), // 3 iron
	COLOR(133,  76,  48), // 4 earth
	COLOR( 52, 101,  36), // 5 moss
	COLOR(208,  70,  72), // 6 berry
	COLOR(117, 113,  97), // 7 olive

	COLOR( 89, 125, 206), // 8 cornflower
	COLOR(210, 125,  44), // 9 ocher
	COLOR(133, 149, 161), // A slate
	COLOR(109, 170,  44), // B leaf
	COLOR(210, 170, 153), // C peach
	COLOR(109, 194, 202), // D sky
	COLOR(218, 212,  94), // E maize
	COLOR(222, 238, 214)  // F peppermint
};

float vertices[] =
{
	0, 0,
	0, 1,
	1, 1,

	0, 0,
	1, 1,
	1, 0
};

Display::Display():
	renderWidth(0),
	renderHeight(0)
{
	Logger::info(TAG, "Initializing display");

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	shader = Shader::Builder()
			.withFile(GL_VERTEX_SHADER, "assets/display.vsh")
			.withFile(GL_FRAGMENT_SHADER, "assets/display.fsh")
			.build();

	shader->bind();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	shader->vertexAttribPointer("aPosition", 2, GL_FLOAT, GL_FALSE, 0, 0);
	glUniform1i(shader->getUniformLocation("uTex"), 0);
	shader->release();
}

void Display::render(Eigen::Matrix4f& mv, Eigen::Matrix4f& p)
{
	shader->bind();
	shader->enableVertexAttrib("aPosition");

	Eigen::Matrix4f mvp = p * mv;

	glUniformMatrix4fv(shader->getUniformLocation("uMVPMatrix"), 1, GL_FALSE, mvp.data());
	glUniform2f(shader->getUniformLocation("uSize"), renderWidth, renderHeight);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	shader->disableVertexAttrib("aPosition");
	shader->release();
}

void Display::resize(int width, int height)
{
	renderWidth = width;
	renderHeight = height;
}

void Display::write(uint8_t *data)
{
	for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
		pixels[i] = palette[data[i] & 0xF];

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

Display::~Display()
{
	Logger::info(TAG, "Destroying display");
	glDeleteBuffers(1, &vbo);
	glDeleteTextures(1, &texture);
}
