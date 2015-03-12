#ifndef R_MODEL_H 
#define R_MODEL_H

#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "Material.h"
#include "RString.h"
namespace rb
{
	class Model
	{
	public:
		Shader* shader;
		Material material;

		Model();
		Model(String path);
		Model(String path, Shader* shader);
		virtual ~Model();
		virtual void Render() const;

	private:
		std::vector<class Mesh> meshes;
		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		class Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	};
}
#endif
