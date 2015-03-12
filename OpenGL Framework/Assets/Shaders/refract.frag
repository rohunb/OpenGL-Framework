#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;

uniform vec3 uViewPos;
uniform samplerCube uCubeMap;

out vec4 outColour;

void main()
{    
	float refractIndex = 1.52f;
	vec3 viewDir = normalize(fragPosition - uViewPos);
    vec3 refractDir = refract(viewDir, normalize(fragNormal), 1.0f/refractIndex);
	outColour = texture(uCubeMap, refractDir);
}