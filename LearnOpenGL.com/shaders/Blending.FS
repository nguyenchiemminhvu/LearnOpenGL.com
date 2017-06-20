#version 330 core

varying vec2 UV;

uniform sampler2D tex;

void main()
{
    vec4 color = texture(tex, UV);

	// remove this code, use blending instead
	// if(color.a < 0.1)
	//		discard;

	gl_FragColor = color;
}