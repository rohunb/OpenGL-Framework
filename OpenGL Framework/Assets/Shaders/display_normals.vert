#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out VertOut{
	vec3 normal;
} vertOut;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(inPosition, 1.0f);
	mat3 normalMatrix = mat3(transpose(inverse(uView * uModel)));
	vertOut.normal = normalize(vec3(uProjection * vec4(normalMatrix * inNormal, 1.0f)));
}