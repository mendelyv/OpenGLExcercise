#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	this->position = position;
	this->worldUp = worldUp;
	forward = glm::normalize(target - position);
	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(forward, right));
}

Camera::~Camera()
{

}


glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + forward, worldUp);
}