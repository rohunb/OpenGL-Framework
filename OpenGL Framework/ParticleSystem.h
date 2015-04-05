#ifndef R_PARTICLE_SYSTEM_H_
#define R_PARTICLE_SYSTEM_H_

#include <vector>
#include <glew.h>
#include "RVector.h"
#include "Texture.h"

namespace rb
{
	class ParticleSystem
	{
	public:
		ParticleSystem(Texture texture, class Shader* shader, size_t numParticles);
		~ParticleSystem();
		void Render(class Camera* camera) const;
	private:
		void Init();
		std::vector<Vec3> positions;
		std::vector<Vec3> colours;
		Vec3 colour;
		size_t numParticles;
		Shader* shader;
		Texture texture;
		GLuint VAO;
		class Random* rand;
	};
}












//namespace rb
//{
//	struct Particle
//	{
//		Vec2 position, velocity;
//		Vec4 colour;
//		Particle() 
//			: Particle(Vec2(0.0f))
//		{}
//		Particle(const Vec2& position)
//			: Particle(position, Vec2(0.0f), Vec4(1.0f))
//		{}
//		Particle(const Vec2& position, const Vec2& velocity, const Vec4& colour)
//			:position(position), velocity(velocity), colour(colour)
//		{}
//	};
//	class ParticleSystem
//	{
//	public:
//		ParticleSystem(Texture texture, class Shader* shader, GLuint numParticles);
//		~ParticleSystem();
//		void Update(float dt);
//		void Render(class Camera* camera) const;
//	private:
//		std::vector<Particle> particles;
//		GLuint numParticles;
//		Shader* shader;
//		Texture texture;
//		GLuint VAO;
//
//		void Init();
//	};
//}
#endif // R_PARTICLE_SYSTEM_H_
