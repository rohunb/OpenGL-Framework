#ifndef R_SIMPLE_MODEL_H_
#define R_SIMPLE_MODEL_H_
#include <vector>
#include "Model.h"
#include "RVector.h"
namespace rb
{
	enum PrimitiveType { Cube, Sphere, QuadSphere };
	class SimpleModel : public Model
	{
	public:
		SimpleModel(PrimitiveType type, Shader* shader, Material material);
		~SimpleModel();
		void Render() const override;
	private:
		PrimitiveType type;
		GLuint VAO, VBO, EBO;
		int numVertices;
		int index;
		int numIndices;
		std::vector<GLfloat> vertices;
		std::vector<GLfloat> normals;
		std::vector<GLuint> indices;
		Vec3 *vertex;
		std::vector <Vec3> Qvertices;
		Vec3 *Qnormals;
		glm::vec2 *QtexCoords;

		void SetupCube();
		void SetupSphere();
		void SetupQuadSphere();
		void LoadFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d);
		void DivideFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d, int count);
		void SphericalNormals();
	};
}
#endif // !R_SIMPLE_MODEL_H_

