#ifndef R_MESH_H_
#define R_MESH_H_
#include <vector>
#include <glew.h>
#include "RVector.h"
#include "Material.h"
namespace rb
{
	struct Vertex
	{
		Vec3 position;
		Vec3 normal;
		Vec2 uvCoord;
	};

	class Mesh
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Material& material);
		~Mesh();
		void Render() const;

	private:
		GLuint VAO, VBO, EBO;
		Material material;
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		//std::vector<struct Texture> textures;
	};
}
#endif // !R_MESH_H_
