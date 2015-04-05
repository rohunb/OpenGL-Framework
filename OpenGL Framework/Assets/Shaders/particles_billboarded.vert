#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColour;

uniform mat4 uView;

out VertOut{
	vec4 colour;
} vertOut;

void main()
{
	gl_Position = uView * vec4(inPosition, 1.0f);
	vertOut.colour = vec4(inColour,1.0f);
}