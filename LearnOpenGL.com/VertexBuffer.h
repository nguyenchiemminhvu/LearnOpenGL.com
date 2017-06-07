#ifndef __VERTEX_BUFFER_H__
#define __VERTEX_BUFFER_H__

#pragma once
#include "glew\glew.h"
#include "glfw\glfw3.h"

class VertexBuffer
{
public:

	VertexBuffer();
	VertexBuffer(const GLsizei size, const GLvoid *data);
	virtual ~VertexBuffer();

	void setData(const GLsizei size, const GLvoid *data);

	GLuint getID();

	void bind();
	void unbind();
	void deleteBuffer();

	void renderBuffer(GLenum mode, GLint first, GLsizei count);

private:
	
	GLuint vertexBufferID;

};

#endif //__VERTEX_BUFFER_H__