#include "RenderBuffer.h"



RenderBuffer::RenderBuffer()
{
	glGenRenderbuffers(1, &renderBufferID);
}


RenderBuffer::~RenderBuffer()
{

}


void RenderBuffer::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);
}


void RenderBuffer::unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}


void RenderBuffer::setBufferStorage(int w, int h, GLenum internalFormat)
{
	glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, w, h);
}


void RenderBuffer::renderFrameBuffer(GLenum attachment)
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderBufferID);
}

