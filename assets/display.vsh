#version 150

in vec4 aPosition;

uniform mat4 uMVPMatrix;

void main()
{
	gl_Position = uMVPMatrix * aPosition;
}