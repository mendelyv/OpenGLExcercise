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
	Material(Shader* shader, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 ambient, float shininess);
	~Material();

	Shader* shader;
	glm::vec3 diffuse;
	glm::vec3 ambient;
	glm::vec3 specular;
	float shininess;
};


#endif