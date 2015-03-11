#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;

uniform vec3 uViewPos;
uniform samplerCube uCubeMap;

out vec4 outColour;

void main()
{    
	vec3 viewDir = normalize(fragPosition - uViewPos);
    vec3 reflectDir = reflect(viewDir, normalize(fragNormal));
	outColour = texture(uCubeMap, reflectDir);
}