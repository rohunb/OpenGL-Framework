#pragma once
#include <glm\glm.hpp>

class Camera
{
public:
	Camera(const glm::vec3& _position = glm::vec3(0.0f));
	Camera(const glm::vec3& _position, const glm::vec3& up, const glm::mat4& _orientation);
	Camera(float _fovY, float _aspectRatio, float _nearClipDistance, float _farClipDistance);
	Camera(const glm::vec3& _position, const glm::vec3& _up, const glm::mat4& _orientation,
		float _fovY, float _aspectRatio, float _nearClipDistance, float _farClipDistance);

	~Camera();

	inline glm::vec3 Position() const {return position;}
	glm::vec3 Up() const;
	glm::vec3 LookPoint() const;
	glm::mat4 View() const;
	glm::mat4 Projection() const;
	void SetProjection(float fovY, float aspectRatio, float nearClipDistance, float farClipDistance);
	void MoveCamera(glm::vec3& direction);
	void RotateCamera(float angle, const glm::vec3& axis);


private:
	glm::vec3 position, forward, up, right, worldUp;
	glm::mat4 orientation;
	float fovY, aspectRatio, nearClipDistance, farClipDistance;
	glm::mat4 viewMatrix, projectionMatrix;

	void Init();
	void Recalculate();
};

