#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp);
	~Camera();

	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;

	float pitch;
	float yaw;

	float forwardSpeed = 0.0f;
	float rightSpeed = 0.0f;
	float upSpeed = 0.0f;

	glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(float deltaX, float deltaY);
	void UpdateCameraPosition();

private:
	void UpdateCameraVector();
};