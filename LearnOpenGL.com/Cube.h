#pragma once

#include "glew\glew.h"
#include "glfw\glfw3.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Texture.h"

class Cube
{
public:
	Cube(const char *diffuseTex = nullptr, const char *specularTex = nullptr);
	virtual ~Cube();

	float vertices[36 * 8];
	Texture diffuse;
	Texture specular;

	bool hasDiffuse;
	bool hasSpecular;
};

