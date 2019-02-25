#pragma once

#ifndef __LIGHTDIRECTIONAL_H__
#define __LIGHTDIRECTIONAL_H__

#include <glm.hpp>
#include <gtx/vector_angle.hpp>
//#include <gtc/matrix_transform.hpp>

class LightDirectional 
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 angles;
	glm::vec3 direction;

public:
	LightDirectional();
	LightDirectional(glm::vec3 position, glm::vec3 angles, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightDirectional();

	void UpdateDirection();
};


#endif