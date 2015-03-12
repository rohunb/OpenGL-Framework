#ifndef R_CAMERA_H_
#define R_CAMERA_H_

#include "RVector.h"
#include "RMatrix.h"

namespace rb
{
	class Camera
	{
	public:

		Camera(const Vec3& _position = Vec3(0.0f));
		Camera(const Vec3& _position, const Vec3& up, const Mat4& _orientation);
		Camera(float _fovY, float _aspectRatio, float _nearClipDistance, float _farClipDistance);
		Camera(const Vec3& _position, const Vec3& _up, const Mat4& _orientation,
			float _fovY, float _aspectRatio, float _nearClipDistance, float _farClipDistance);

		~Camera();

		inline Vec3 Position() const { return position; }
		Vec3 Up() const;
		Vec3 LookPoint() const;
		Mat4 View() const;
		Mat4 Projection() const;
		void SetProjection(float fovY, float aspectRatio, float nearClipDistance, float farClipDistance);
		void MoveCamera(Vec3& direction);
		void RotateCamera(float angle, const Vec3& axis);


	private:
		Vec3 position, forward, up, right, worldUp;
		Mat4 orientation;
		float fovY, aspectRatio, nearClipDistance, farClipDistance;
		Mat4 viewMatrix, projectionMatrix;

		void Init();
		void Recalculate();
	};
}
#endif // !R_CAMERA_H_
