#pragma once

#include "glew\glew.h"
#include "glfw\glfw3.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Texture.h"

class Plane
{
public:

	Plane(const char *tex = nullptr);
	~Plane();

	float vertices[6 * 8];
	Texture diffuse;

	bool hasDiffuse;

};

