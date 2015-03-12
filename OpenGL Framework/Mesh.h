#ifndef R_MESH_H_
#define R_MESH_H_
#include <vector>
#include <glew.h>
#include "RVector.h"
namespace rb
{
	struct Vertex
	{
		Vec3 position;
		Vec3 normal;
		Vec2 texCoord;
	};

	class Mesh
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<struct Texture>& textures);
		~Mesh();
		void Render() const;

	private:
		GLuint VAO, VBO, EBO;
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<struct Texture> textures;
	};
}
#endif // !R_MESH_H_
