#ifndef __ELEMENT_BUFFER_H__
#define __ELEMENT_BUFFER_H__

#pragma once
#include "glew\glew.h"
#include "glfw\glfw3.h"

class ElementBuffer
{
public:

	ElementBuffer();
	ElementBuffer(GLsizeiptr size, const void *data);
	virtual ~ElementBuffer();

	void setData(GLsizeiptr size, const void *data);

	GLuint getID();
	
	void bind();
	void unbind();
	void deleteBuffer();
	void renderElements(GLenum mode, GLsizei count, GLenum type, const void *indices);

private:

	GLuint elementBufferID;

};

#endif //__ELEMENT_BUFFER_H__