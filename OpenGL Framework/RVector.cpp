#include "RVector.h"

float rb::RVector::Magnitude(const Vec3& vector)
{
	return glm::length(vector);
}
