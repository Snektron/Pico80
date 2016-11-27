uniform sampler2D uTexture;
uniform sampler2D uPalette;

varying vec2 vTexCoords;

void main()
{
	float index = texture2D(uTexture, vTexCoords).x;
	vec2 palcoord = vec2(index * 16.0, 0);
	vec3 color = texture2D(uPalette, palcoord).xyz;
	gl_FragColor = vec4(color, 1);
}
