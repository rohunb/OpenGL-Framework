#include "GameObject.h"
#include "RMatrix.h"
using namespace rb;
GameObject::GameObject(Model* _model)
	: model(_model),
	position(Vec3(0.0f)),
	rotation(Mat4(1.0f)),
	scale(Vec3(1.0f))
{
}

GameObject::GameObject(Model* _model, const Vec3& _position,
	const Mat4& _rotation /*= Mat4(1.0f)*/, const Vec3& _scale /*= Vec3(1.0f)*/)
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

Mat4 GameObject::GetTransform() const
{
	return RMatrix::Translate(position)
		* rotation
		* RMatrix::Scale(scale);
}

void GameObject::SetTransform(const Vec3& position, const Mat4& rotation, const Vec3& scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

void GameObject::Update(float dt)
{

}
