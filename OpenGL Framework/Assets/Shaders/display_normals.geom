#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VertOut{
    vec3 normal;
}vertIn[];

const float size = 0.2f;

void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(vertIn[index].normal, 0.0f) * size;
    EmitVertex();
    EndPrimitive();
}

void main()
{
	GenerateLine(0); // First vertex normal
    GenerateLine(1); // Second vertex normal
    GenerateLine(2); // Third vertex normal
}