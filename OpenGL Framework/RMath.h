#ifndef R_MATH_H_
#define R_MATH_H_
#include <glm\gtx\rotate_vector.hpp>
//#include "glm\gtx\norm.hpp"
#include "RVector.h"

namespace rb
{
	class RMath
	{
	public:
		//Vector
		static Vec3 RotateY(const Vec3& vector, float angle);
	};
}
#endif // !R_MATH_H_
