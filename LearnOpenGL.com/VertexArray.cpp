#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vertexArrayID);
}


VertexArray::~VertexArray()
{
	deleteArray();
}

GLuint VertexArray::getID()
{
	return this->vertexArrayID;
}

void VertexArray::bind()
{
	glBindVertexArray(vertexArrayID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::deleteArray()
{
	glDeleteVertexArrays(1, &vertexArrayID);
}

void VertexArray::vertexAttribArray(GLuint index, GLsizei size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VertexArray::enableAttribute(GLuint index) {
	glEnableVertexAttribArray(index);
}