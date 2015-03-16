#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;

uniform vec3 uViewPos;
uniform samplerCube uCubeMap;

out vec4 outColour;

void main()
{    
	float refractIndex = 1.52f;
	vec3 norm = normalize(fragNormal);
	vec3 viewDir = normalize(fragPosition - uViewPos);
	vec3 reflectDir = reflect(viewDir, norm);
    vec3 refractDir = refract(viewDir, norm, 1.0f/refractIndex);
	
	vec4 reflectColour = texture(uCubeMap, reflectDir);
	vec4 refractColour = texture(uCubeMap, refractDir);
	float mixPercent = pow(dot(norm, -viewDir), 1);
	outColour = mix(reflectColour, refractColour, mixPercent);
}