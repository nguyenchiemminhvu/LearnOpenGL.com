#ifndef __WINDOW_H__
#define __WINDOW_H__

#pragma once

#include <glew\glew.h>
#include <glfw\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "ColorFrameBuffer.h"
#include "Texture.h"
#include "Camera.h"
#include "Model.h"

#include "Material.h"
#include "Cube.h"
#include "Plane.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using std::vector;

static bool keysPressed[1024] = { false };
static bool firstMouseEvent = false;
static Camera mainCamera;

class Window
{
public:

	enum WindowProperties
	{
		WIDTH = 800,
		HEIGHT = 600
	};

	enum FPS
	{
		FPS = 60
	};

	Window(const GLchar *title, GLuint width = WIDTH, GLuint height = HEIGHT);
	virtual ~Window();

	void enable(GLenum feature);
	void disable(GLenum feature);
	void windowHint(int target, int hint);
	void windowViewport(GLint x, GLint y, GLuint width, GLuint height);

	int windowShouldClose();
	void setWindowShouldClose(int value);
	void clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	void clear(GLbitfield mask);
	void swapBuffer();

	void setMousePos(double x, double y);
	void disableCursor();
	void hideCursor();
	void showCursor();

	void setKeyCallback(GLFWkeyfun func);
	void setMouseButtonCallback(GLFWmousebuttonfun func);
	void setCursorPosCallback(GLFWcursorposfun func);

	/**************/
	int exec();
	void terminate();
	/**************/

private:

	GLFWwindow *window;

	void initTime();
	void initCallbackFunction();
};

#include <stdio.h>
static void checkingError(const GLchar *operation) {
	for (GLint error = glGetError(); error; error = glGetError()) {
		printf("%s - glError(0x%x)\n", operation, error);
	}
}

#endif //__WINDOW_H__