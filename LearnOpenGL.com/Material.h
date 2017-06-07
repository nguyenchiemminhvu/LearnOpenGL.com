#pragma once

#include <glew\glew.h>
#include <glfw\glfw3.h>
#include <glm\glm.hpp>

enum MaterialName
{
	EMERALD,
	JADE,
	OBSIDIAN,
	PEARL,
	RUBY,
	TURQUOISE,
	BRASS,
	BRONZE,
	CHROME,
	COPPER,
	GOLD,
	SILVER,

	TOTAL
};

class Material
{
public:

	Material() {};
	Material(MaterialName materialName);
	~Material();

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

private:

	glm::vec3	getAmbient(MaterialName materialName);
	glm::vec3	getDiffuse(MaterialName materialName);
	glm::vec3	getSpecular(MaterialName materialName);
	float		getShininess(MaterialName materialName);
};