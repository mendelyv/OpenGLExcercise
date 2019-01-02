#pragma once

#include "Shader.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#ifndef __MATERIAL__
#define  __MATERIAL__


class Material
{
public:
	Material();
	Material(Shader* shader, unsigned int diffuse, unsigned int specular, unsigned int emission, glm::vec3 ambient, float shininess);
	~Material();

	Shader* shader;
	unsigned int diffuse;
	glm::vec3 ambient;
	unsigned int specular;
	unsigned int emission;
	float shininess;
};


#endif