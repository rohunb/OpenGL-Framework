#ifndef R_MODEL_H 
#define R_MODEL_H

#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
//#include "Shader.h"
#include "Material.h"
#include "RString.h"
namespace rb
{
	class Model
	{
	public:
		class Shader* shader;
		Material material;
		Model();
		Model(const string& path);
		Model(const string& path, class Shader* shader);
		Model(const string& path, const Material& material, class Shader* shader);
		virtual ~Model();
		virtual void Render() const;

	private:
		string directory;
		std::vector<class Mesh> meshes;
		void LoadModel(const std::string& path, bool useModelMaterial);
		void ProcessNode(aiNode* node, const aiScene* scene, bool useModelMaterial);
		class Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, bool useModelMaterial);
		struct Texture LoadMaterialTexture(aiMaterial* aiMat, aiTextureType type);

	};
}
#endif
