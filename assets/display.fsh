#version 130

uniform sampler2D uTex;

in vec2 uv;

void main()
{
	gl_FragColor = vec4(texture(uTex, vec2(uv.x, 1-uv.y)).xyz, 1.0);
}