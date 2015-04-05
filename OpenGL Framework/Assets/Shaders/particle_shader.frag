#version 330 core

//in vec2 fragTexCoord;
//in vec4 fragParticleColour;

//uniform sampler2D diffuseTexture;
uniform vec3 uColour;
out vec4 outColour;

void main()
{    
	//outColour = texture(diffuseTexture, fragTexCoord) * fragParticleColour;
	outColour = vec4(1.0f,0.0f,0.0f,1.0f);
	//outColour = uColour;
}