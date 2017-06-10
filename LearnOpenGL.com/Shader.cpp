#include "Shader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using std::cout;
using std::stringstream;
using std::ifstream;
using std::string;


Shader::Shader()
{

}


Shader::Shader(const Shader & other)
{
	glDeleteProgram(this->shaderProgram);
	this->shaderProgram = other.shaderProgram;
}


Shader::Shader(GLchar *vertexPath, GLchar *fragmentPath)
{
	retriveShaderFile(vertexPath, fragmentPath);
}


void Shader::setupShader(GLchar * vertexPath, GLchar * fragmentPath)
{
	retriveShaderFile(vertexPath, fragmentPath);
}


GLuint Shader::getProgramID()
{
	return shaderProgram;
}


GLint Shader::getAttribLocation(const char * name)
{
	return glGetAttribLocation(shaderProgram, name);
}


void Shader::use()
{
	glUseProgram(shaderProgram);
}

void Shader::deleteShader()
{
	glDeleteProgram(shaderProgram);
}

void Shader::setUniform1i(const char * name, GLint v0)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name), v0);
}

void Shader::setUniform1f(const char * name, GLfloat v0)
{
	glUniform1f(glGetUniformLocation(shaderProgram, name), v0);
}

void Shader::setUniform1d(const char * name, GLdouble v0)
{
	glUniform1d(glGetUniformLocation(shaderProgram, name), v0);
}

void Shader::setUniform1iv(const char * name, GLsizei count, const GLint * value)
{
	glUniform1iv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform1fv(const char * name, GLsizei count, const GLfloat * value)
{
	glUniform1fv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform1dv(const char * name, GLsizei count, const GLdouble * value)
{
	glUniform1dv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform2i(const char * name, GLint x, GLint y)
{
	glUniform2i(glGetUniformLocation(shaderProgram, name), x, y);
}

void Shader::setUniform2f(const char * name, GLfloat x, GLfloat y)
{
	glUniform2f(glGetUniformLocation(shaderProgram, name), x, y);
}

void Shader::setUniform2d(const char * name, GLdouble x, GLdouble y)
{
	glUniform2d(glGetUniformLocation(shaderProgram, name), x, y);
}

void Shader::setUniform2iv(const char * name, GLsizei count, const GLint * value)
{
	glUniform2iv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform2fv(const char * name, GLsizei count, const GLfloat * value)
{
	glUniform2fv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform2dv(const char * name, GLsizei count, const GLdouble * value)
{
	glUniform2dv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform3i(const char * name, GLint x, GLint y, GLint z)
{
	glUniform3i(glGetUniformLocation(shaderProgram, name), x, y, z);
}

void Shader::setUniform3f(const char * name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(glGetUniformLocation(shaderProgram, name), x, y, z);
}

void Shader::setUniform3d(const char * name, GLdouble x, GLdouble y, GLdouble z)
{
	glUniform3d(glGetUniformLocation(shaderProgram, name), x, y, z);
}

void Shader::setUniform3iv(const char * name, GLsizei count, const GLint * value)
{
	glUniform3iv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform3fv(const char * name, GLsizei count, const GLfloat * value)
{
	glUniform3fv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform3dv(const char * name, GLsizei count, const GLdouble * value)
{
	glUniform3dv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform4i(const char * name, GLint x, GLint y, GLint z, GLint w)
{
	glUniform4i(glGetUniformLocation(shaderProgram, name), x, y, z, w);
}

void Shader::setUniform4f(const char * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(glGetUniformLocation(shaderProgram, name), x, y, z, w);
}

void Shader::setUniform4d(const char * name, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	glUniform4d(glGetUniformLocation(shaderProgram, name), x, y, z, w);
}

void Shader::setUniform4iv(const char * name, GLsizei count, const GLint * value)
{
	glUniform4iv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform4fv(const char * name, GLsizei count, const GLfloat * value)
{
	glUniform4fv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform4dv(const char * name, GLsizei count, const GLdouble * value)
{
	glUniform4dv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniformMatrix2fv(const char * name, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name), count, transpose, value);
}

void Shader::setUniformMatrix2dv(const char * name, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	glUniformMatrix2dv(glGetUniformLocation(shaderProgram, name), count, transpose, value);
}

void Shader::setUniformMatrix3fv(const char * name, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name), count, transpose, value);
}

void Shader::setUniformMatrix3dv(const char * name, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	glUniformMatrix3dv(glGetUniformLocation(shaderProgram, name), count, transpose, value);
}

void Shader::setUniformMatrix4fv(const char * name, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), count, transpose, value);
}

void Shader::setUniformMatrix4dv(const char * name, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	glUniformMatrix4dv(glGetUniformLocation(shaderProgram, name), count, transpose, value);
}

void Shader::setUniformSubroutines(const GLchar *routineName, const GLchar *uniformName, GLenum shaderType, GLsizei count, const GLuint *indices)
{
	GLuint routineIndex = glGetSubroutineIndex(shaderProgram, shaderType, routineName);
	GLuint routineLocation = glGetSubroutineUniformLocation(shaderProgram, shaderType, uniformName);
	glUniformSubroutinesuiv(shaderType, count, indices);
}

void Shader::retriveShaderFile(GLchar * vertexPath, GLchar * fragmentPath)
{
	ifstream vertexShaderFile, fragmentShaderFile;
	stringstream vertexShaderStream, fragmentShaderStream;
	string vShader, fShader;

	vertexShaderFile.exceptions(std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vShader = vertexShaderStream.str();
		fShader = fragmentShaderStream.str();
	}
	catch (const std::exception &e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	vertexShaderFile.close();
	fragmentShaderFile.close();

	const GLchar *vertexShaderCode = vShader.c_str();
	const GLchar *fragmentShaderCode = fShader.c_str();
	compileShaderCode(vertexShaderCode, fragmentShaderCode);
}

void Shader::compileShaderCode(const GLchar * vertexShaderCode, const GLchar * fragmentShaderCode)
{
	GLuint vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	attachShader(vertexShader, fragmentShader);
}

void Shader::attachShader(GLint vertexShader, GLint fragmentShader)
{
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}