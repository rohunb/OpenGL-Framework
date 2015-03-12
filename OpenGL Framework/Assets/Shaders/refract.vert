#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 fragPosition;
out vec3 fragNormal;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(inPosition, 1.0f);
	fragPosition = vec3(uModel * vec4(inPosition, 1.0f));
    fragNormal = mat3(transpose(inverse(uModel))) * inNormal;
}