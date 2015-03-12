#ifndef R_GAMEOBJECT_H_
#define R_GAMEOBJECT_H_
#include "Model.h"
#include "RVector.h"
#include "RMatrix.h"
namespace rb
{
	class GameObject
	{
	public:
		Vec3 position, scale;
		Mat4 rotation;

		GameObject(Model* model);
		GameObject(Model* model, const Vec3& position, const Mat4& rotation = Mat4(1.0f), const Vec3& scale = Vec3(1.0f));
		virtual ~GameObject();

		inline Model* GetModel() const { return model; }

		Mat4 GetTransform() const;
		void SetTransform(const Vec3& position, const Mat4& rotation, const Vec3& scale);

		virtual void Update(float dt);

	private:
		Model* model;
	};
}
#endif

