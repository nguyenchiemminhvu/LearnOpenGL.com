#version 330 core

varying vec3 FragPos;
varying vec3 Normal;
varying vec2 UV;

uniform sampler2D texture_diffuse1;

void main()
{
	gl_FragColor = texture(texture_diffuse1, UV);
}