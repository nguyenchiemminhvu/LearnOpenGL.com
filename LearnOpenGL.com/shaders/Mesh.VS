#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

varying vec3 FragPos;
varying vec3 Normal;
varying vec2 UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);

	// calculate light with model space
	FragPos = vec3(model * vec4(position, 1.0F));
	Normal = mat3(transpose(inverse(model))) * normal;
	UV = uv;
}