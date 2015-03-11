#version 330 core

uniform vec3 uColour;
out vec4 outColour;

void main()
{    
	outColour = vec4(uColour,1.0f);
}