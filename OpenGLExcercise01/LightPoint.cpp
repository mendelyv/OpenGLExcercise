#include "LightPoint.h"

LightPoint::LightPoint()
{

}

LightPoint::LightPoint(glm::vec3 position, glm::vec3 angles, glm::vec3 color)
{
	this->position = position;
	this->angles = angles;
	this->color = color;

	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
}

LightPoint::~LightPoint()
{

}