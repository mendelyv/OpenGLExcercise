#pragma once

#ifndef __LIGHTSPOT_H__
#define __LIGHTSPOT_H__

#include <glm.hpp>
#include <gtx/vector_angle.hpp>
//#include <gtc/matrix_transform.hpp>

class LightSpot
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 angles;
	glm::vec3 direction;
	float cosPhyInner;
	float cosPhyOutter;

	//光衰减的公式参数
	float constant;
	float linear;
	float quadratic;

public:
	LightSpot();
	LightSpot(glm::vec3 position, glm::vec3 angles, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightSpot();

	void UpdateDirection();
};

#endif