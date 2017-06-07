#include <glew\glew.h>
#include <glfw\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Texture.h"
#include "Camera.h"
#include "Model.h"

#include "Material.h"
#include "Cube.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

static void checkingError(const GLchar *operation) {
	for (GLint error = glGetError(); error; error = glGetError()) {
		printf("%s - glError(0x%x)\n", operation, error);
	}
}

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

int main()
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
	GLFWwindow *window = glfwCreateWindow(1024, 768, "Learn OpenGL 3", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// -------------------------------------------------------------
	// init glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		return -2;
	}

	// -------------------------------------------------------------
	// setup GL Viewport
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// -------------------------------------------------------------
	// setup callbacks
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// -------------------------------------------------------------
	// disable mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// -------------------------------------------------------------
	// setup before game loop
	glEnable(GL_DEPTH_TEST);

	// -------------------------------------------------------------
	// Enable writing to the stencil buffer.
	// Render objects, updating the content of the stencil buffer.
	// Disable writing to the stencil buffer.
	// Render(other) objects, this time discarding certain fragments based on the content of the stencil buffer.
	glEnable(GL_STENCIL_TEST);

	last_time = cur_time = glfwGetTime();

	Shader shader("shaders/Mesh.VS", "shaders/Mesh.FS");
	Model model("models/castle/Castle.obj");

	// OpenGL loop
	while (!glfwWindowShouldClose(window))
	{
		// poll events
		glfwPollEvents();
		
		// updating
		last_time = cur_time;
		cur_time = glfwGetTime();
		deltaTime = cur_time - last_time;

		updateCamera();

		// drawing
		glClearColor(0.1F, 0.4F, 0.5F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		model.Draw(shader);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
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
