#version 130

attribute vec4 aPosition;

uniform mat4 uMVPMatrix;

varying vec2 uv;

void main()
{
	uv = aPosition.xy / 2.0 + 0.5;
	gl_Position = uMVPMatrix * (aPosition * vec4(0.95, 0.95, 1.0, 1.0));
}