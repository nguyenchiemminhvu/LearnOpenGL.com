#ifndef __RENDER_BUFFER_H__
#define __RENDER_BUFFER_H__

#pragma once

#include <glew\glew.h>
#include <glfw\glfw3.h>

class RenderBuffer
{
public:

	GLuint renderBufferID;

	RenderBuffer();
	virtual ~RenderBuffer();

	void bind();
	void unbind();
	
	void setBufferStorage(int w, int h, GLenum internalFormat);
	void renderFrameBuffer(GLenum attachment);

private:

};

#endif //__RENDER_BUFFER_H__