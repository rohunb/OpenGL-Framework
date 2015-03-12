#ifndef R_MATRIX_H
#define R_MATRIX_H
#include "RVector.h"
namespace rb
{
	using Mat4 = glm::mat4;
	class RMatrix
	{
	public:
		static Mat4 Perspective(float fovY, float aspectRatio, float nearClipDistance, float farClipDistance);
		static Mat4 LookAt(const Vec3& position, const Vec3& lookAtPoint, const Vec3& up);
		static Mat4 Translate(const Vec3& translate);
		static Mat4 Scale(const Vec3& scale);
		static const float* ValuePtr(const Mat4& matrix);
	};


}
#endif