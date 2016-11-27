attribute highp vec4 aVertices;
attribute highp vec2 aTexCoords;

uniform highp vec2 uScale;

varying vec2 vTexCoords;

void main()
{
	vTexCoords = aTexCoords;
	gl_Position = vec4(aVertices.xy * uScale, 0, 1);
}
