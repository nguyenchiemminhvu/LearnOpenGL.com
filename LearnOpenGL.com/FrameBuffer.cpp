#include "FrameBuffer.h"



FrameBuffer::FrameBuffer()
	: isAttachedTexture(false)
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

GLenum FrameBuffer::checkBufferStatus()
{
	return glCheckFramebufferStatus(GL_FRAMEBUFFER);
}


bool FrameBuffer::isBufferCompleted()
{
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}


bool FrameBuffer::hasAttachedTexture2D()
{
	return isAttachedTexture;
}


void FrameBuffer::createTextureAndAttach2D(int w, int h, GLenum attachment)
{
	unsigned int tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, textureFormatFromAttachment(attachment), textureTypeFromAttachment(attachment), NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, tex, 0);
	isAttachedTexture = true;
}


GLenum FrameBuffer::textureFormatFromAttachment(GLenum attachment)
{
	switch (attachment)
	{
	case GL_COLOR_ATTACHMENT0:
		return GL_UNSIGNED_BYTE;
		
	case GL_DEPTH_ATTACHMENT:
		return GL_DEPTH_COMPONENT;

	case GL_STENCIL_ATTACHMENT:
		return GL_STENCIL_INDEX;

	case GL_DEPTH_STENCIL_ATTACHMENT:
		return GL_DEPTH_STENCIL;

	default:
		return GL_ZERO;
	}
}


GLenum FrameBuffer::textureTypeFromAttachment(GLenum attachment)
{
	switch (attachment)
	{
	case GL_COLOR_ATTACHMENT0:
		return GL_UNSIGNED_BYTE;

	case GL_DEPTH_ATTACHMENT:
		return GL_UNSIGNED_BYTE;

	case GL_STENCIL_ATTACHMENT:
		return GL_UNSIGNED_BYTE;

	case GL_DEPTH_STENCIL_ATTACHMENT:
		return GL_UNSIGNED_INT_24_8;

	default:
		return GL_ZERO;
	}
}

