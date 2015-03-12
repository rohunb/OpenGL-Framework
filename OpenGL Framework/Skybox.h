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
		Skybox(GLuint textureID);
		~Skybox();
		void Render(class Camera* camera) const;
		inline GLuint TextureID() const { return textureID; }
		Shader* shader;
	private:
		GLuint VAO, VBO, EBO;
		GLuint textureID;
		SimpleModel* skyboxModel;
		void Init();
	};
}

#endif // !R_SKYBOX_H_
