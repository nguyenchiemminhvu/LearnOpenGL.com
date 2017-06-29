#include "FrameBuffer.h"



FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &frameBufferID);
}


FrameBuffer::~FrameBuffer()
{
	deleteBuffer();
}


void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
}


void FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void FrameBuffer::deleteBuffer()
{
	glDeleteBuffers(1, &frameBufferID);
}

