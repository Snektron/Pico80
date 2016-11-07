#version 150

uniform sampler2D uTex;
uniform vec2 uResolution;

void main()
{
	vec2 uv = gl_FragCoord.xy/uResolution;
	gl_FragColor = vec4(texture(uTex, uv).xyz, 1);
}