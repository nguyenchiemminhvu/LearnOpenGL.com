#include "Plane.h"



Plane::Plane(const char * tex)
{
	float planeVertices[] = {
		// positions          // texture Coords
		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	memcpy(this->vertices, vertices, (36 * 8) * sizeof(GLfloat));

	if (tex)
	{
		diffuse.bind();
		diffuse.loadImage(tex);
		diffuse.generateMipmap();
		diffuse.textureParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
		diffuse.textureParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
		diffuse.textureParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		diffuse.textureParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		diffuse.unbind();

		hasDiffuse = true;
	}
}


Plane::~Plane()
{

}
