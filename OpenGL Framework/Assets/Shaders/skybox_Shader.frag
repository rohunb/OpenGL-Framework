#version 330 core

in vec3 fragTexCoord;
out vec4 outColour;
uniform samplerCube uCubeMap;

void main()
{    
	outColour = texture(uCubeMap,fragTexCoord);
}