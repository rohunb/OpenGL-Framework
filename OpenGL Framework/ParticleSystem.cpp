#include "ParticleSystem.h"
#include "Shader.h"
#include "Camera.h"
#include "Debug.h"
#include "RRandom.h"

using namespace rb;

rb::ParticleSystem::ParticleSystem(Shader* shader, size_t numParticles)
	:shader(shader), numParticles(numParticles)
{
	Init();
}

rb::ParticleSystem::~ParticleSystem()
{
	if(rand) delete rand;
}

void rb::ParticleSystem::Render(class Camera* camera) const
{
	shader->Use();
	GLuint viewLoc = shader->GetStdUniformLoc(Shader::StdUniform::ViewMatrix);
	GLuint projLoc = shader->GetStdUniformLoc(Shader::StdUniform::ProjectionMatrix);
	GLuint colourLoc = glGetUniformLocation(shader->Program(), "uColour");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, RMatrix::ValuePtr(camera->View()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, RMatrix::ValuePtr(camera->Projection()));
	glUniform3f(colourLoc, 1.0f, 0.0f, 0.0f);
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, numParticles);
	glBindVertexArray(0);
	glUseProgram(0);
}

void rb::ParticleSystem::Init()
{
	//rand=new Random(0.0f, 10.0f);
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(-3.0f, 3.0f);
	for (size_t i = 0; i < numParticles; i++)
	{
		positions.push_back(Vec3(dist(mt), dist(mt), 0.0f));
		//Debug::Info("Position: " + std::to_string(positions[i].x) + ","+std::to_string(positions[i].y));
	}

	GLuint VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, numParticles * sizeof(Vec3), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}














//rb::ParticleSystem::ParticleSystem(Texture texture, Shader* shader, GLuint numParticles) 
//	:texture(texture),
//	numParticles(numParticles),
//	shader(shader)
//{
//	Init();
//}
//
//rb::ParticleSystem::~ParticleSystem()
//{
//
//}
//
//void rb::ParticleSystem::Update(float dt)
//{
//
//}
//
//void rb::ParticleSystem::Render(Camera* camera) const
//{
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//	shader->Use();
//	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::StdUniform::ProjectionMatrix), 1, GL_FALSE, RMatrix::ValuePtr(camera->Projection()));
//	for (const Particle& particle: particles)
//	{
//		glUniform2f(glGetUniformLocation(shader->Program(), "uPosition"), particle.position.x, particle.position.y);
//		glUniform4f(glGetUniformLocation(shader->Program(), "uColour"), particle.colour.x, particle.colour.y, particle.colour.z, particle.colour.w);
//		glUniform1i(glGetUniformLocation(shader->Program(), "diffuseTexture"), 0);
//		glBindTexture(GL_TEXTURE_2D, texture.texID);
//		glBindVertexArray(VAO);
//		Debug::Info("Draw Particle at pos " + std::to_string(particle.position.x) + "," + std::to_string(particle.position.y));
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//		glBindVertexArray(0);
//	}
//	glUseProgram(0);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//}
//
//void rb::ParticleSystem::Init()
//{
//
//	//GLuint VBO;
//	//GLfloat quadVertices[] = 
//	//{
//	//	0.0f, 1.0f, 0.0f, 1.0f,
//	//	1.0f, 0.0f, 1.0f, 0.0f,
//	//	0.0f, 0.0f, 0.0f, 0.0f,
//
//	//	0.0f, 1.0f, 0.0f, 1.0f,
//	//	1.0f, 1.0f, 1.0f, 1.0f,
//	//	1.0f, 0.0f, 1.0f, 0.0f
//	//};
//	//glGenVertexArrays(1, &VAO);
//	//glGenBuffers(1, &VBO);
//	//glBindVertexArray(VAO);
//	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
//	//glEnableVertexAttribArray(0);
//	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
//	//glBindVertexArray(0);
//	////float startPosX = -50.0f;
//	//for (size_t i = 0; i < numParticles; ++i)
//	//{
//	//	//particles.push_back(Particle(Vec2(startPosX)));
//	//	particles.push_back(Particle());
//	//	//startPosX += 1.0f;
//	//}
//
//	//GLfloat g_vertex_buffer_data[] = {
//	//	-0.5f, -0.5f, 0.0f,
//	//	0.5f, -0.5f, 0.0f,
//	//	-0.5f, 0.5f, 0.0f,
//	//	0.5f, 0.5f, 0.0f,
//	//};
//	//GLuint billboard_vertex_buffer;
//	//glGenBuffers(1, &billboard_vertex_buffer);
//	//glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
//
//	//// The VBO containing the positions and sizes of the particles
//	//GLuint particles_position_buffer;
//	//glGenBuffers(1, &particles_position_buffer);
//	//glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
//	//// Initialize with empty (NULL) buffer : it will be updated later, each frame.
//	//glBufferData(GL_ARRAY_BUFFER, numParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
//
//	//// The VBO containing the colors of the particles
//	//GLuint particles_color_buffer;
//	//glGenBuffers(1, &particles_color_buffer);
//	//glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
//	//// Initialize with empty (NULL) buffer : it will be updated later, each frame.
//	//glBufferData(GL_ARRAY_BUFFER, numParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
//
//	//// Update the buffers that OpenGL uses for rendering.
//	//// There are much more sophisticated means to stream data from the CPU to the GPU, 
//	//// but this is outside the scope of this tutorial.
//	//// http://www.opengl.org/wiki/Buffer_Object_Streaming
//
//	//glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
//	//glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
//	//glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_particule_position_size_data);
//
//	//glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
//	//glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
//	//glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLubyte) * 4, g_particule_color_data);
//}

