#include "ElementBuffer.h"


ElementBuffer::ElementBuffer()
{
	glGenBuffers(1, &elementBufferID);
}


ElementBuffer::ElementBuffer(GLsizeiptr size, const void *data)
{
	glGenBuffers(1, &elementBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


ElementBuffer::~ElementBuffer()
{
	deleteBuffer();
}


void ElementBuffer::setData(GLsizeiptr size, const void * data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


GLuint ElementBuffer::getID()
{
	return this->elementBufferID;
}


void ElementBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
}


void ElementBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void ElementBuffer::deleteBuffer()
{
	glDeleteBuffers(1, &elementBufferID);
}


void ElementBuffer::renderElements(GLenum mode, GLsizei count, GLenum type, const void *indices)
{
	glDrawElements(mode, count, type, indices);
}