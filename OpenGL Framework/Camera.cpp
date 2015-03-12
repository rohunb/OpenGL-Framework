#include "Camera.h"
#include "RMatrix.h"
#include "RMath.h"
using namespace rb;
Camera::Camera(const Vec3& _position /*= Vec3(0.0f)*/)
	: position(_position),
	worldUp(Vec3(0.0f, 1.0f, 0.0f)),
	orientation(Mat4(1.0f)),
	fovY(53.13f), aspectRatio(1.0f), nearClipDistance(0.1f), farClipDistance(1000.0f)
{
	Init();
}

Camera::Camera(const Vec3& _position, const Vec3& up, const Mat4& _orientation)
	: position(_position),
	worldUp(up),
	orientation(_orientation),
	fovY(53.13f), aspectRatio(1.0f), nearClipDistance(0.1f), farClipDistance(1000.0f)
{
	Init();
}

Camera::Camera(float _fovY, float _aspectRatio, float _nearClipDistance, float _farClipDistance)
	: position(Vec3(0.0f)),
	worldUp(Vec3(0.0f, 1.0f, 0.0f)),
	orientation(Mat4(1.0f)),
	fovY(_fovY),
	aspectRatio(_aspectRatio),
	nearClipDistance(_nearClipDistance),
	farClipDistance(_farClipDistance)
{
	Init();
}

Camera::Camera(const Vec3& _position, const Vec3& _up, const Mat4& _orientation, 
	float _fovY, float _aspectRatio, float _nearClipDistance, float _farClipDistance)

	:position(_position),
	worldUp(_up),
	orientation(_orientation),
	fovY(_fovY),
	aspectRatio(_aspectRatio),
	nearClipDistance(_nearClipDistance),
	farClipDistance(_farClipDistance)
{
	Init();
}
Camera::~Camera()
{

}

Vec3 Camera::Up() const
{
	return up;
}

Vec3 Camera::LookPoint() const
{
	return position + forward;
}

Mat4 Camera::View() const
{
	return RMatrix::LookAt(position, position + forward, up);
}

Mat4 Camera::Projection() const
{
	return projectionMatrix;
}

void Camera::SetProjection(float fovY, float aspectRatio, float nearClipDistance, float farClipDistance)
{
	projectionMatrix = RMatrix::Perspective(fovY, aspectRatio, nearClipDistance, farClipDistance);
}

void Camera::MoveCamera(Vec3& direction)
{
	float dirMag = RVector::Magnitude(direction);
	if (dirMag < 0.01f)
	{
		return;
	}
	direction /= dirMag;
	float angle = glm::acos(glm::dot(direction, Vec3(0.0f, 0.0f, -1.0f)));
	if (direction.x > 0.0f)
	{
		angle *= -1.0f;
	}
	Vec3 moveDir = RMath::RotateY(forward, glm::degrees(angle));
	position += moveDir * dirMag;
}

void Camera::RotateCamera(float angle, const Vec3& axis)
{
	orientation = glm::rotate(orientation, angle, axis);
	Recalculate();
}

void Camera::Recalculate()
{
	forward = Vec3(orientation * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(right, forward));
}

void Camera::Init()
{
	Recalculate();
	SetProjection(fovY, aspectRatio, nearClipDistance, farClipDistance);
}
