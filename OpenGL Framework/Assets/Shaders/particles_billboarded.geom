#version 330 core
layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 4) out;

uniform mat4 uProjection;
uniform float uSize;

in VertOut{
	vec4 colour;
} vertOut[];

out vec2 vertUV;
out vec4 vertColour;

void main()
{
	vec4 pos = gl_in[0].gl_Position;
	
	//bottom left
	vec2 botLeft = pos.xy + vec2(-0.5f,-0.5f) * uSize;
	gl_Position = uProjection * vec4(botLeft, pos.zw);
	vertUV = vec2(0.0f,0.0f);
	vertColour = vertOut[0].colour;
	EmitVertex();

	//top left
	vec2 topLeft = pos.xy + vec2(-0.5f,0.5f) * uSize;
	gl_Position = uProjection * vec4(topLeft, pos.zw);
	vertUV = vec2(0.0f,1.0f);
	vertColour = vertOut[0].colour;
	EmitVertex();

	//bottom right
	vec2 botRight = pos.xy + vec2(0.5f,-0.5f) * uSize;
	gl_Position = uProjection * vec4(botRight, pos.zw);
	vertUV = vec2(1.0f,0.0f);
	vertColour = vertOut[0].colour;
	EmitVertex();

	//top right
	vec2 topRight = pos.xy + vec2(0.5f,0.5f) * uSize;
	gl_Position = uProjection * vec4(topRight, pos.zw);
	vertUV = vec2(1.0f,1.0f);
	vertColour = vertOut[0].colour;
	EmitVertex();

	EndPrimitive();
}