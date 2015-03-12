#include "RVector.h"
using namespace rb;

Vec3 rb::RVector::up = Vec3(0.0f,1.0f,0.0f);
Vec3 rb::RVector::down = -up;
Vec3 rb::RVector::left = Vec3(-1.0f,0.0f,0.0f);
Vec3 rb::RVector::right = -left;
Vec3 rb::RVector::forward = Vec3(0.0f, 0.0f, -1.0f);
Vec3 rb::RVector::back = -forward;

float rb::RVector::Magnitude(const Vec3& vector)
{
	return glm::length(vector);
}
