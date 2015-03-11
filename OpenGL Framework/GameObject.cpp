#include "GameObject.h"
#include "glm/gtc/matrix_transform.hpp"

GameObject::GameObject(Model* _model)
	: model(_model),
	position(glm::vec3(0.0f)),
	rotation(glm::mat4(1.0f)),
	scale(glm::vec3(1.0f))
{

}

GameObject::GameObject(Model* _model, const glm::vec3& _position,
	const glm::mat4& _rotation /*= glm::mat4(1.0f)*/, const glm::vec3& _scale /*= glm::vec3(1.0f)*/)
	: model(_model),
	position(_position),
	rotation(_rotation),
	scale(_scale)
{
}

GameObject::~GameObject()
{
	if (model)
	{
		delete model;
		model = nullptr;
	}
}

glm::mat4 GameObject::GetTransform() const
{
	return glm::translate(glm::mat4(1.0f), position)
		* rotation
		* glm::scale(glm::mat4(1.0f), scale);
}

void GameObject::SetTransform(const glm::vec3& position, const glm::mat4& rotation, const glm::vec3& scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

void GameObject::Update(float dt)
{

}
