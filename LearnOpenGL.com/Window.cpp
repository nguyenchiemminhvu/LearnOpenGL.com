#include "Window.h"
#include <stdlib.h>
#include <iostream>

#define __CURRENT_LESSION__ 3

#define __GET_STARTED__		1
#define __LIGHTING__		2
#define __MODEL__ 			3
#define __DEPTH_TEST__		4
#define __STENCIL_TEST__	5

using std::cout;
using std::endl;


int isFlashLightOn = 1; // 1 is on, 0 is off

// callbacks
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void cursor_callback(GLFWwindow *window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

double last_time = glfwGetTime(), cur_time = glfwGetTime();
double deltaTime = 0.0F;

Camera camera(glm::vec3(0.0F, 0.0F, 3.0F));
int width, height;
bool cameraKey[Camera::CameraDirection::TOTAL_KEY];
bool cameraFirstMouseInput = true;
double cameraMouseX = 0.0F, cameraMouseY = 0.0F;
void updateCamera();


Window::Window(const GLchar *title, GLuint width, GLuint height)
{
	// -------------------------------------------------------------
	// init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

	// -------------------------------------------------------------
	// create GLFW Window and current context
	window = glfwCreateWindow(1024, 768, "Learn OpenGL 3", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	// -------------------------------------------------------------
	// init glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		exit(-2);
	}

	// -------------------------------------------------------------
	// setup GL Viewport
	glfwGetFramebufferSize(window, &::width, &::height);
	glViewport(0, 0, ::width, ::height);

	// -------------------------------------------------------------
	// disable mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	initCallbackFunction();
	initTime();

	disableCursor();
	firstMouseEvent = false;
}


Window::~Window()
{
	terminate();
}

#if (__CURRENT_LESSION__ == __GET_STARTED__)

#elif (__CURRENT_LESSION__ == __LIGHTING__)

#elif (__CURRENT_LESSION__ == __MODEL__)
int Window::exec() {

	// --------------------------------------------------------------
	// prepare for game loop

	// Enable writing to the stencil buffer.
	// Render objects, updating the content of the stencil buffer.
	// Disable writing to the stencil buffer.
	// Render(other) objects, this time discarding certain fragments based on the content of the stencil buffer.
	glEnable(GL_DEPTH_TEST);

	Shader shader("shaders/Mesh.VS", "shaders/Mesh.FS");
	Model model("models/house/farmhouse_obj.obj");
	


	// --------------------------------------------------------------
	// game loop
	while (!windowShouldClose())
	{
		glfwPollEvents();

		::deltaTime = glfwGetTime() - ::last_time;
		::last_time = glfwGetTime();
		/* calculate FPS */
		GLfloat fps = 1.0f / deltaTime;
		while (glfwGetTime() - ::last_time < 1.0f / FPS) {

		}
		updateCamera();

		// drawing
		glClearColor(0.1F, 0.4F, 0.5F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		model.Draw(shader);

		swapBuffer();
	}

	return 0;
}

#elif (__CURRENT_LESSION__ == __STENCIL_TEST__)

int Window::exec() {

	// --------------------------------------------------------------
	// prepare for game loop

	// Enable writing to the stencil buffer.
	// Render objects, updating the content of the stencil buffer.
	// Disable writing to the stencil buffer.
	// Render(other) objects, this time discarding certain fragments based on the content of the stencil buffer.
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);



	// --------------------------------------------------------------
	// game loop
	while (!windowShouldClose())
	{
		glfwPollEvents();

		::deltaTime = glfwGetTime() - ::last_time;
		::last_time = glfwGetTime();
		/* calculate FPS */
		GLfloat fps = 1.0f / deltaTime;
		while (glfwGetTime() - ::last_time < 1.0f / FPS) {

		}
		updateCamera();

		// drawing
		glClearColor(0.1F, 0.4F, 0.5F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		

		swapBuffer();
	}

	return 0;
}

#endif


void Window::terminate() {
	glfwTerminate();
}


void Window::setMousePos(double x, double y) {
	glfwSetCursorPos(window, x, y);
}


void Window::disableCursor() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Window::hideCursor() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}


void Window::showCursor() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::setKeyCallback(GLFWkeyfun func)
{
	glfwSetKeyCallback(window, func);
}

void Window::setMouseButtonCallback(GLFWmousebuttonfun func)
{
	glfwSetMouseButtonCallback(window, func);
}

void Window::setCursorPosCallback(GLFWcursorposfun func)
{
	glfwSetCursorPosCallback(window, func);
}


void Window::clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
	glClearColor(red, green, blue, alpha);
}


void Window::clear(GLbitfield mask) {
	glClear(mask);
}


void Window::swapBuffer() {
	glfwSwapBuffers(window);
}


int Window::windowShouldClose() {
	return glfwWindowShouldClose(window);
}


void Window::setWindowShouldClose(int value) {
	glfwSetWindowShouldClose(window, value);
}


void Window::enable(GLenum feature) {
	glEnable(feature);
}


void Window::disable(GLenum feature) {
	glDisable(feature);
}


void Window::windowHint(int target, int value) {
	glfwWindowHint(target, value);
}


void Window::windowViewport(GLint x, GLint y, GLuint width, GLuint height) {
	glViewport(x, y, width, height);
}


void Window::initTime() {
	::last_time = glfwGetTime();
	::deltaTime = 0;
}


void Window::initCallbackFunction() {
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
}


void updateCamera()
{
	if (cameraKey[Camera::CameraDirection::FORWARD])
		camera.processKeyboard(Camera::CameraDirection::FORWARD, deltaTime);
	if (cameraKey[Camera::CameraDirection::BACKWARD])
		camera.processKeyboard(Camera::CameraDirection::BACKWARD, deltaTime);
	if (cameraKey[Camera::CameraDirection::LEFT])
		camera.processKeyboard(Camera::CameraDirection::LEFT, deltaTime);
	if (cameraKey[Camera::CameraDirection::RIGHT])
		camera.processKeyboard(Camera::CameraDirection::RIGHT, deltaTime);
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == GLFW_KEY_F && action == GLFW_RELEASE)
	{
		if (isFlashLightOn)
			isFlashLightOn = 0;
		else
			isFlashLightOn = 1;
	}

	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
			cameraKey[Camera::CameraDirection::FORWARD] = true;
		if (key == GLFW_KEY_S)
			cameraKey[Camera::CameraDirection::BACKWARD] = true;
		if (key == GLFW_KEY_A)
			cameraKey[Camera::CameraDirection::LEFT] = true;
		if (key == GLFW_KEY_D)
			cameraKey[Camera::CameraDirection::RIGHT] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_W)
			cameraKey[Camera::CameraDirection::FORWARD] = false;
		if (key == GLFW_KEY_S)
			cameraKey[Camera::CameraDirection::BACKWARD] = false;
		if (key == GLFW_KEY_A)
			cameraKey[Camera::CameraDirection::LEFT] = false;
		if (key == GLFW_KEY_D)
			cameraKey[Camera::CameraDirection::RIGHT] = false;
	}
}

void cursor_callback(GLFWwindow *window, double xPos, double yPos)
{
	if (cameraFirstMouseInput)
	{
		cameraFirstMouseInput = false;
		lastPosX = xPos;
		lastPosY = yPos;
	}

	GLfloat xOffset = xPos - lastPosX;
	GLfloat yOffset = lastPosY - yPos;

	lastPosX = xPos;
	lastPosY = yPos;

	camera.processMouseMovement(xOffset, yOffset);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{

}
