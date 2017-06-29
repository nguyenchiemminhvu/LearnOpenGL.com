#version 330 core

varying vec2 UV;

uniform sampler2D tex;

void main()
{
    vec4 color = vec4(vec3(1.0 - texture(tex, UV)), texture(tex, UV).a);

	gl_FragColor = color;
}