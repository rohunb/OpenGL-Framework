#version 330 core
layout (location = 0) in vec3 inPosition;
//layout (location = 1) in vec3 inColour;

uniform mat4 uView;
uniform mat4 uProjection;
//uniform vec2 uPosition;
//uniform vec4 uColour;

//out vec2 fragTexCoord;
//out vec4 fragParticleColour;

void main()
{
	//fragParticleColour = vec4(inColour,1.0f);
	gl_Position = uProjection * uView * vec4(inPosition, 1.0f);

}