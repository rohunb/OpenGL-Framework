#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Position;
in vec3 Normal;

out vec4 color;

#define NUM_LIGHTS 3

uniform vec3 viewPos;
uniform Material material;
uniform Light lights[NUM_LIGHTS];
//uniform Light light;
vec3 CalcPointLight(Light light, Material mat, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
    // Properties
    vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - Position);
	vec3 result = vec3(0.0f);
	for	(int i = 0; i < NUM_LIGHTS; i++)
	{
		result+=CalcPointLight(lights[i], material, norm, Position, viewDir);    
	}
	color = vec4(result, 1.0f);
    
    //color = vec4(ambientColor + diffuseColor + specularColor, 1.0f);
	//color = vec4(0.0f,1.0f,0.0f,1.0f);
}
vec3 CalcPointLight(Light light, Material mat, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos); 
    
    // Diffuse shading    
    float diffuse = max(dot(normal, lightDir), 0.0);
    
    // Specular shading    
    vec3 reflectDir = reflect(-lightDir, normal);
    float specular = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);

    // Combine results
    vec3 ambientColor = light.ambient * mat.diffuse;
    vec3 diffuseColor = light.diffuse * diffuse * mat.diffuse;
    vec3 specularColor = light.specular * specular * mat.specular;
	vec3 result = ambientColor + diffuseColor + specularColor;
	return result;
}