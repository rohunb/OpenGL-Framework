#pragma once
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
};

