
#include "LightSpot.h"

LightSpot::LightSpot()
{

}

LightSpot::LightSpot(glm::vec3 position, glm::vec3 angles, glm::vec3 color)
{
	this->position = position;
	this->angles = angles;
	this->color = color;
	//this->direction = glm::vec3(0, 0, 1.0f);
	cosPhyInner = 0.9f;
	cosPhyOutter = 0.85;
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
	UpdateDirection();
}

void LightSpot::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction *= -1.0f;
}

LightSpot::~LightSpot()
{

}