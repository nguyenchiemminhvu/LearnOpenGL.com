#include "VertexBuffer.h"


VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &vertexBufferID);
}


VertexBuffer::VertexBuffer(const GLsizei size, const GLvoid *data)
{
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


VertexBuffer::~VertexBuffer()
{
	deleteBuffer();
}


void VertexBuffer::setData(const GLsizei size, const GLvoid * data)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


GLuint VertexBuffer::getID()
{
	return this->vertexBufferID;
}


void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
}


void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void VertexBuffer::deleteBuffer()
{
	glDeleteBuffers(1, &vertexBufferID);
}

void VertexBuffer::renderBuffer(GLenum mode, GLint first, GLsizei count)
{
	glDrawArrays(mode, first, count);
}