#version 330 core

uniform vec3 eyePos;
#version 330 core

varying vec2 UV;

uniform sampler2D tex;

void main()
{
	gl_FragColor = texture(tex, UV);
}