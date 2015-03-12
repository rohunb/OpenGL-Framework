#include "RMatrix.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace rb;
Mat4 RMatrix::Perspective(float fovY, float aspectRatio, float nearClipDistance, float farClipDistance)
{
	return glm::perspective(fovY, aspectRatio, nearClipDistance, farClipDistance);
}

Mat4 RMatrix::LookAt(const Vec3& position, const Vec3& lookAtPoint, const Vec3& up)
{
	return glm::lookAt(position, lookAtPoint, up);
}

Mat4 rb::RMatrix::Translate(const Vec3& translate)
{
	return glm::translate(Mat4(1.0f), translate);
}

Mat4 rb::RMatrix::Scale(const Vec3& scale)
{
	return glm::scale(Mat4(1.0f), scale);
}

const float* rb::RMatrix::ValuePtr(const Mat4& matrix)
{
	return glm::value_ptr(matrix);
}
