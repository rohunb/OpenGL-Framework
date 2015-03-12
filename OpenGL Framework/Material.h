#ifndef R_MATERIAL_H_
#define R_MATERIAL_H_
#include <glew.h>
#include "RVector.h"
namespace rb
{
	struct Material
	{
		Vec3 diffuse;
		GLuint diffuseTextureID;
		Vec3 specular;
		float shininess;

		Material()
			:diffuse(Vec3(1.0f)),
			diffuseTextureID(0),
			specular(Vec3(1.0f)),
			shininess(4.0f)
		{}
		Material(const Vec3& _diffuseColour)
			:diffuse(_diffuseColour),
			diffuseTextureID(0),
			specular(Vec3(1.0f)),
			shininess(4.0f)
		{}
		Material(const Vec3& _diffuseColour, const Vec3& _specularColour, float _shininess)
			:diffuse(_diffuseColour),
			diffuseTextureID(0),
			specular(_specularColour),
			shininess(_shininess)
		{}
		Material(GLuint _diffuseTextureID, const Vec3& _specularColour, float _shininess)
			:diffuse(Vec3(1.0f)),
			diffuseTextureID(_diffuseTextureID),
			specular(_specularColour),
			shininess(_shininess)
		{}
		Material(GLuint _diffuseTextureID)
			:diffuseTextureID(_diffuseTextureID),
			diffuse(Vec3(1.0f)),
			specular(Vec3(1.0f)),
			shininess(4.0f)
		{}
	};
}
#endif // !R_MATERIAL_H_
