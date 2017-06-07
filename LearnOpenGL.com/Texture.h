#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#pragma once
#include "glew\glew.h"
#include "glfw\glfw3.h"
#include "SOIL\SOIL.h"

#include <string>

using std::string;

class Texture
{
public:
	static void active(GLuint index);

	Texture();
	virtual ~Texture();

	void setTextureID(GLuint id);
	GLuint getTextureID();
	string getTextureType();
	string getPath();
	void setTextureType(string type);
	void setPath(const string &path);

	void bind();
	void unbind();
	void textureParameteri(GLenum pname, GLint value);
	void generateMipmap();
	void loadImage(const char *path);

private:
	GLuint textureID;
	string type;
	string path;
	int width;
	int height;
};

#endif //__TEXTURE_H__