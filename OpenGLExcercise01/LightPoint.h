#pragma once

#ifndef __LIGHTPOINT_H__
#define __LIGHTPOINT_H__

#include <glm.hpp>
#include <gtx/vector_angle.hpp>
//#include <gtc/matrix_transform.hpp>

class LightPoint
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 angles;
	glm::vec3 direction;

	//光衰减的公式参数
	float constant;
	float linear;
	float quadratic;

public:
	LightPoint();
	LightPoint(glm::vec3 position, glm::vec3 angles, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint();
};

#endif