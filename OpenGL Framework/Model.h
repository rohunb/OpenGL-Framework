#ifndef R_MODEL_H 
#define R_MODEL_H

#include <vector>
#include <string>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "Material.h"

class Model
{
public:
	Shader* shader;
	Material material;

	Model();
	virtual ~Model();
	virtual void Render() const;

private:
	std::vector<class Mesh> meshes;
	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh);

};

#endif
