#ifndef __SHADER_H__
#define __SHADER_H__

#pragma once
#include "glew\glew.h"

class Shader
{
public:

	Shader();
	Shader(const Shader &other);
	Shader(GLchar *vertexPath, GLchar *fragmentPath);

	void setupShader(GLchar *vertexPath, GLchar *fragmentPath);

	GLuint getProgramID();
	GLint getAttribLocation(const char *name);

	void use();
	void deleteShader();

	void setUniform1i(const char *name, GLint v0);
	void setUniform1f(const char *name, GLfloat v0);
	void setUniform1d(const char *name, GLdouble v0);
	void setUniform1iv(const char *name, GLsizei count, const GLint *value);
	void setUniform1fv(const char *name, GLsizei count, const GLfloat *value);
	void setUniform1dv(const char *name, GLsizei count, const GLdouble *value);

	void setUniform2i(const char *name, GLint x, GLint y);
	void setUniform2f(const char *name, GLfloat x, GLfloat y);
	void setUniform2d(const char *name, GLdouble x, GLdouble y);
	void setUniform2iv(const char *name, GLsizei count, const GLint *value);
	void setUniform2fv(const char *name, GLsizei count, const GLfloat *value);
	void setUniform2dv(const char *name, GLsizei count, const GLdouble *value);

	void setUniform3i(const char *name, GLint x, GLint y, GLint z);
	void setUniform3f(const char *name, GLfloat x, GLfloat y, GLfloat z);
	void setUniform3d(const char *name, GLdouble x, GLdouble y, GLdouble z);
	void setUniform3iv(const char *name, GLsizei count, const GLint *value);
	void setUniform3fv(const char *name, GLsizei count, const GLfloat *value);
	void setUniform3dv(const char *name, GLsizei count, const GLdouble *value);

	void setUniform4i(const char *name, GLint x, GLint y, GLint z, GLint w);
	void setUniform4f(const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setUniform4d(const char *name, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	void setUniform4iv(const char *name, GLsizei count, const GLint *value);
	void setUniform4fv(const char *name, GLsizei count, const GLfloat *value);
	void setUniform4dv(const char *name, GLsizei count, const GLdouble *value);

	void setUniformMatrix2fv(const char *name, GLsizei count, GLboolean transpose, const GLfloat *value);
	void setUniformMatrix2dv(const char *name, GLsizei count, GLboolean transpose, const GLdouble *value);

	void setUniformMatrix3fv(const char *name, GLsizei count, GLboolean transpose, const GLfloat *value);
	void setUniformMatrix3dv(const char *name, GLsizei count, GLboolean transpose, const GLdouble *value);

	void setUniformMatrix4fv(const char *name, GLsizei count, GLboolean transpose, const GLfloat *value);
	void setUniformMatrix4dv(const char *name, GLsizei count, GLboolean transpose, const GLdouble *value);

	void setUniformSubroutines(const GLchar *routineName, const GLchar *uniformName, GLenum shaderType, GLsizei count, const GLuint *indices);

private:
	GLuint shaderProgram;

	void retriveShaderFile(GLchar *vertexPath, GLchar *fragmentPath);
	void compileShaderCode(const GLchar *vertexShaderCode, const GLchar *fragmentShaderCode);
	void attachShader(GLint vertexShader, GLint fragmentShader);
};

#endif //__SHADER_H__