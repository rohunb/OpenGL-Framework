#ifndef R_LIGHT_H_
#define R_LIGHT_H_

#include "RVector.h"
namespace rb
{
	struct Light
	{
		Vec3 position;
		Vec3 ambient;
		Vec3 diffuse;
		Vec3 specular;

		~Light(){}
		Light()
			:position(Vec3(0.0f)),
			ambient(Vec3(1.0f)),
			diffuse(Vec3(1.0f)),
			specular(Vec3(1.0f))
		{}
		Light(const Vec3& _position, const Vec3& _ambient, const Vec3& _diffuse, const Vec3& _specular)
			:position(_position),
			ambient(_ambient),
			diffuse(_diffuse),
			specular(_specular)
		{}
	};
}
#endif // !R_LIGHT_H_
