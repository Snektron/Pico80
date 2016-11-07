#version 130

in vec4 aPosition;

uniform mat4 uMVPMatrix;
uniform vec2 uSize;

out vec2 uv;

void main()
{
    vec2 pos = aPosition.xy;
	uv = aPosition.xy / 2.0 + 0.5;
	gl_Position = uMVPMatrix * vec4(uSize * aPosition.xy, 0, 1);
}