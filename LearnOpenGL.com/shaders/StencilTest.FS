#version 330 core

varying vec3 Color;
varying vec2 UV;

uniform sampler2D tex;
uniform vec3 reflectionColor;

void main()
{
	gl_FragColor = reflectionColor * vec4(Color, 1.0f) * texture(tex, UV);
}