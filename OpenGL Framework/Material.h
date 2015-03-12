#ifndef R_MATERIAL_H_
#define R_MATERIAL_H_
#include <glew.h>
#include "RVector.h"
#include "Texture.h"
namespace rb
{
	class Material
	{
	public:
		Material()
			:Material(Vec3(1.0f))
		{}
		Material(const Vec3& diffuseColour)
			:Material(Vec3(1.0f), Vec3(1.0f), 4.0f)
		{}
		Material(const Vec3& diffuseColour, const Vec3& specularColour, float shininess)
			:Material(Texture(), diffuseColour, specularColour, shininess)
		{}
		Material(const Texture& diffuseTexture)
			:Material(diffuseTexture, Vec3(1.0f), 4.0f)
		{}
		Material(const Texture& diffuseTexture, const Vec3& specularColour, float shininess)
			:Material(diffuseTexture, Vec3(1.0f), specularColour, shininess)
		{}

		Vec3 Diffuse() const { return diffuse; }
		Texture DiffuseTexture() const { return diffuseTexture; }
		Vec3 Specular() const { return specular; }
		float Shininess() const { return shininess; }

	private:
		Vec3 diffuse;
		Texture diffuseTexture;
		Vec3 specular;
		float shininess;
		Material(const Texture& _diffuseTexture, const Vec3& _diffuseColour, const Vec3& _specularColour, float _shininess)
			:diffuseTexture(_diffuseTexture),
			diffuse(_diffuseColour),
			specular(_specularColour),
			shininess(_shininess)
		{}
	};
}
#endif // !R_MATERIAL_H_
