#include "ColorFrameBuffer.h"



ColorFrameBuffer::ColorFrameBuffer()
	: colorBufferCounter(0)
{
	glGenFramebuffers(1, &colorFrameBufferID);
}


ColorFrameBuffer::~ColorFrameBuffer()
{
	
}


void ColorFrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, colorFrameBufferID);
}


void ColorFrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void ColorFrameBuffer::createAndAttachTexture(int w, int h)
{
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorBufferCounter, GL_TEXTURE_2D, colorFrameBufferID, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	colorBufferCounter++;
	textureSize.push_back(std::pair<int, int>(w, h));
}
