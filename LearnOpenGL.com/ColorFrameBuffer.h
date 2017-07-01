#ifndef __COLOR_FRAME_BUFFER_H__
#define __COLOR_FRAME_BUFFER_H__

#pragma once

#include <glew\glew.h>
#include <glfw\glfw3.h>

#include <vector>

class ColorFrameBuffer
{
public:

	GLuint colorFrameBufferID;
	int colorBufferCounter;
	std::vector<std::pair<int, int>> textureSize;

	ColorFrameBuffer();
	virtual ~ColorFrameBuffer();

	void bind();
	void unbind();

	void createAndAttachTexture(int w, int h);

private:

};

#endif //__COLOR_FRAME_BUFFER_H__