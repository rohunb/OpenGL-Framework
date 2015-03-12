#ifndef R_VECTOR_H_
#define R_VECTOR_H_

#include <glm\glm.hpp>

namespace rb
{
	using Vec3 = glm::vec3;
	using Vec2 = glm::vec2;
	using Vec4 = glm::vec4;
	class RVector
	{
	public:
		static Vec3 up, down, left, right, forward, back;
		static float Magnitude(const Vec3& vector);
	};
}
#endif