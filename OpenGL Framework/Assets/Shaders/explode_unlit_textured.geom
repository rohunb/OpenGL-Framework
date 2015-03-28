#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VertOut{
    vec2 texCoord;
}vertIn[];

uniform float uTime;
uniform float uExplodeMag;

out vec2 fragTexCoord;

vec4 Explode(vec4 _position, vec3 _normal)
{
    float magnitude = 2.0f;
    vec3 direction = _normal * (sin(uTime * 2.0f) + 1.0f) * uExplodeMag; 
    return _position + vec4(direction, 0.0f);
}
vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main()
{
	vec3 normal = GetNormal();
	gl_Position = Explode(gl_in[0].gl_Position, normal);
    fragTexCoord = vertIn[0].texCoord;
    EmitVertex();
    gl_Position = Explode(gl_in[1].gl_Position, normal);
    fragTexCoord = vertIn[1].texCoord;
    EmitVertex();
    gl_Position = Explode(gl_in[2].gl_Position, normal);
    fragTexCoord = vertIn[2].texCoord;
    EmitVertex();
    EndPrimitive();
}