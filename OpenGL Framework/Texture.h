#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <glew.h>
namespace rb
{
	struct Texture
	{
		enum TextureType { Diffuse, Specular, Normal, CubeMap };
		TextureType texType;
		GLuint texID;

		Texture()
			:Texture(0, Diffuse)
		{
		}
		Texture(GLuint _texID, TextureType _texType)
			:texID(_texID),
			texType(_texType)
		{
		}
	};
}
#endif //TEXTURE_H_
