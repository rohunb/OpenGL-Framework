#version 330 core

in vec2 vertUV;
in vec4 vertColour;

uniform sampler2D diffuseTexture;

out vec4 outColour;

void main()
{    
	vec2 uv = vertUV.xy;
	uv.y *= -1.0f;
	vec3 texColour = texture(diffuseTexture, uv).rgb;
	outColour = vec4(texColour, 1.0f) * vertColour;

	//outColour = vec4(1.0f,1.0f,0.0f,1.0f);

	//outColour = vertColour;
}