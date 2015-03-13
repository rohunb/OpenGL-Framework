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

Vec3 Camera::GetUpVector() const
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
//void Camera::MoveCamera(Vec3& direction)
//{
//	float dirMag = RVector::Magnitude(direction);
//	if (dirMag < 0.01f)
//	{
//		return;
//	}
//	direction /= dirMag;
//	float angle = glm::acos(glm::dot(direction, RVector::forward));
//	if (direction.x > 0.0f)
//	{
//		angle *= -1.0f;
//	}
//	Vec3 moveDir = RMath::RotateY(forward, glm::degrees(angle));
//	position += moveDir * dirMag;
//}
void rb::Camera::Move(MoveDir moveDir, float distance)
{
	switch (moveDir)
	{
	case rb::Camera::Forward:
		position += forward*distance;
		break;
	case rb::Camera::Backward:
		position -= forward*distance;
		break;
	case rb::Camera::Left:
		position -= right*distance;
		break;
	case rb::Camera::Right:
		position += right*distance;
		break;
	case rb::Camera::MoveDir::Up:
		position += up*distance;
		break;
	case rb::Camera::Down:
		position -= up*distance;
		break;
	default:
		break;
	}
}


void Camera::RotateCamera(float angle, const Vec3& axis)
{
	orientation = glm::rotate(orientation, angle, axis);
	Recalculate();
}

void rb::Camera::LookAt(const Vec3& destination)
{
	Vec3 back = glm::normalize(position - destination);
	forward = -back;
	right = glm::cross(back, RVector::up);
	if (RVector::Magnitude(right) < RMath::epsilon)
	{
		right = glm::cross(back, RVector::back);
	}
	if (RVector::Magnitude(right) < RMath::epsilon)
	{
		right = glm::cross(back, RVector::right);
	}
	assert(RVector::Magnitude(right) != 0.0f);
	glm::normalize(right);
	up = glm::normalize(glm::cross(forward, right));
	orientation = Mat4
		(
		right.x, up.x, back.x, 0.0f,
		right.y, up.y,back.y, 0.0f,
		right.z, up.z, back.z, 0.0f,
		-glm::dot(position, right), -glm::dot(position, up), -glm::dot(position, back), 1.0f);
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
