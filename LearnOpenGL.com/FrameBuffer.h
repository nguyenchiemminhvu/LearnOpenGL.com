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

	GLenum checkBufferStatus();
	bool isBufferCompleted();

	// attach texture
	bool hasAttachedTexture2D();
	void createTextureAndAttach2D(int w, int h, GLenum attachment = GL_COLOR_ATTACHMENT0);

private:

	GLuint frameBufferID;

	bool isAttachedTexture;
	GLenum textureFormatFromAttachment(GLenum attachment);
	GLenum textureTypeFromAttachment(GLenum attachment);

};

#endif // __FRAME_BUFFERS_H__