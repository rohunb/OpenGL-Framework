#ifndef R_SKYBOX_H_
#define R_SKYBOX_H_

#include <string>
#include <glew.h>
#include "SimpleModel.h"
#include "Shader.h"
namespace rb
{
	class Skybox
	{
	public:
		Skybox();
		Skybox(std::string textureName);
		Skybox(struct Texture texture);
		~Skybox();
		void Render(class Camera* camera) const;
		struct rb::Texture GetTexture() const;
		Shader* shader;
	private:
		GLuint VAO, VBO, EBO;
		struct Texture texture;
		SimpleModel* skyboxModel;
		void Init();
	};
}

#endif // !R_SKYBOX_H_
