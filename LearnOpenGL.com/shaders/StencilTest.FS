#version 330 core

varying vec3 Color;
varying vec2 UV;

uniform sampler2D tex;

void main()
{
	gl_FragColor = vec4(Color, 1.0f) * texture(tex, UV);
}