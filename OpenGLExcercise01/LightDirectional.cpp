
#include "LightDirectional.h"


LightDirectional::LightDirectional()
{
	direction = glm::vec3(0, 0, 1.0f);
}

LightDirectional::LightDirectional(glm::vec3 position, glm::vec3 angles, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f))
{
	direction = glm::vec3(0, 0, 1.0f);
	this->position = position;
	this->angles = angles;
	this->color = color;
	this->UpdateDirection();
}

LightDirectional::~LightDirectional()
{

}

void LightDirectional::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction *= -1.0f;
}
