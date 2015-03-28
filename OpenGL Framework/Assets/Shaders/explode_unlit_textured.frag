#version 330 core

in vec2 fragTexCoord;

uniform sampler2D diffuseTexture;

out vec4 outColour;

void main()
{
    outColour = texture(diffuseTexture,fragTexCoord);
	//outColour = vec4(1.0f,0.0f,0.0f,1.0f);
}