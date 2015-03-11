#pragma once
#include "glm/glm.hpp"
#include "Model.h"

class GameObject
{
public:
	glm::vec3 position, scale;
	glm::mat4 rotation;

	GameObject(Model* model);
	GameObject(Model* model, const glm::vec3& position, const glm::mat4& rotation = glm::mat4(1.0f), const glm::vec3& scale = glm::vec3(1.0f));
	virtual ~GameObject();
	
	inline Model* GetModel() const { return model; }
	
	glm::mat4 GetTransform() const;
	void SetTransform(const glm::vec3& position, const glm::mat4& rotation, const glm::vec3& scale);

	virtual void Update(float dt);

private:
	Model* model;
};

