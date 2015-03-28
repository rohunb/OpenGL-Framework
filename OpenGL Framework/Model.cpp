#include "Model.h"
#include <iostream>
#include "Mesh.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Material.h"
#include "ShaderManager.h"
#include "Debug.h"
#include "RString.h"
#include "Assets.h"

using namespace rb;

void Model::Render() const
{
	for (Mesh mesh : meshes)
	{
		mesh.Render();
	}

}

Model::Model()
{
	//Debug::Info("Model default ctor");
}
rb::Model::Model(const string& path, const Material& _material, Shader* _shader)
	:material(_material),
	shader(_shader)
{
	LoadModel(Assets::modelsPath+path, false);
}

rb::Model::Model(const string& path, Shader* _shader)
	:shader(_shader)
{
	//Debug::Info("Model:: loading mat from model");
	LoadModel(Assets::modelsPath+path, true);
}

rb::Model::Model(const string& path)
	: Model(path, ShaderManager::GetShader(Shader::ShaderType::Unlit_Untextured))
{}

void rb::Model::LoadModel(const string& path, bool useModelMaterial)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	Debug::Info("Model Directory: " + directory);
	ProcessNode(scene->mRootNode, scene, useModelMaterial);
}

void rb::Model::ProcessNode(aiNode* node, const aiScene* scene, bool useModelMaterial)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene, useModelMaterial));
	}
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene, useModelMaterial);
	}
}

class Mesh rb::Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, bool useModelMaterial)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	//std::vector<Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		Vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		if (mesh->mTextureCoords[0])
		{
			Vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.uvCoord = vec;
		}
		else
		{
			vertex.uvCoord = Vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	if (useModelMaterial)
	{
		aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];
		this->material = LoadMaterialTexture(aiMat, aiTextureType_DIFFUSE);
		//return Mesh(vertices, indices, this->material);
	}
	return Mesh(vertices, indices, this->material);
}//ProcessMesh


struct Texture rb::Model::LoadMaterialTexture(aiMaterial* aiMat, aiTextureType type)
{
	aiString name;
	aiMat->GetTexture(type, 0, &name);
	string texName = string(name.C_Str());
	TextureManager::LoadTextureAbsPath(texName, directory + "/" + texName, Texture::Diffuse);
	Debug::Info("Model Texture: " + texName + " ID: " + std::to_string((TextureManager::GetTexture(texName).texID)));
	return TextureManager::GetTexture(texName);
}

Model::~Model()
{
}


