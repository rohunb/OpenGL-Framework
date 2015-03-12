#include "RMath.h"
using namespace rb;
Vec3 rb::RMath::RotateY(const Vec3& vector, float angle)
{
	return glm::rotateY(vector, angle);
}
