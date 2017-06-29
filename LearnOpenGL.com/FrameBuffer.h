#ifndef __FRAME_BUFFERS_H__
#define __FRAME_BUFFERS_H__

#pragma once

#include "glew\glew.h"
#include "glfw\glfw3.h"

class FrameBuffer
{
public:

	FrameBuffer();
	virtual ~FrameBuffer();

	void bind();
	void unbind();

	void deleteBuffer();

private:

	GLuint frameBufferID;

};

#endif // __FRAME_BUFFERS_H__