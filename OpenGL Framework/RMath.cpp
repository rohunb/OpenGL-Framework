#include "RMath.h"
using namespace rb;

float rb::RMath::epsilon = 0.01f;

Vec3 rb::RMath::RotateY(const Vec3& vector, float angle)
{
	return glm::rotateY(vector, angle);
}
