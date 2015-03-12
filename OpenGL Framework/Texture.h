#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <glew.h>
namespace rb
{
	struct Texture
	{
		enum TextureType { Diffuse, Specular, Normal };
		TextureType texType;
		GLuint texID;
	};
}
#endif //TEXTURE_H_
