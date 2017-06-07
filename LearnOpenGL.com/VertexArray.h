#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

#pragma once
#include "glew\glew.h"
#include "glfw\glfw3.h"

class VertexArray
{
public:
	VertexArray();
	virtual ~VertexArray();

	GLuint getID();

	void bind();
	void unbind();
	void deleteArray();
	void vertexAttribArray(GLuint index, GLsizei size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
	void enableAttribute(GLuint index);

private:
	GLuint vertexArrayID;
};

#endif //__VERTEX_ARRAY_H__