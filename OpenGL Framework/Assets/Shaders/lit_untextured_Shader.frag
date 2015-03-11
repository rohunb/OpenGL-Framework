#version 330 core

struct Material {
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

in vec3 fragPosition;
in vec3 fragNormal;

out vec4 outColor;

uniform vec3 uViewPos;
uniform Material uMaterial;
uniform Light uLight;

vec3 CalcPointLight(Light light, Material mat, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
    // Properties
    vec3 _norm = normalize(fragNormal);
	vec3 _viewDir = normalize(uViewPos - fragPosition);
	vec3 _result = CalcPointLight(uLight, uMaterial, _norm, fragPosition, _viewDir);    
	outColor = vec4(_result, 1.0f);
	
	//outColor = vec4(0.0f,1.0f,0.0f,1.0f);
}
vec3 CalcPointLight(Light light, Material mat, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 _lightDir = normalize(light.position - fragPos); 
    
    // Diffuse shading    
    float _diffuse = max(dot(normal, _lightDir), 0.0);
    
	//blinn phong
	vec3 _halfDir = normalize(_lightDir + viewDir);
	float _specAngle = max(dot(_halfDir, normal),0.0f);
	float _specular = pow(_specAngle, mat.shininess);

    // Phong 
    //vec3 _reflectDir = reflect(-_lightDir, normal);
    //float _specular = pow(max(dot(viewDir, _reflectDir), 0.0), mat.shininess);

    // Combine results
    vec3 _ambientColor = light.ambient * mat.diffuse;
    vec3 _diffuseColor = light.diffuse * _diffuse * mat.diffuse;
    vec3 _specularColor = light.specular * _specular * mat.specular;
	vec3 _result = _ambientColor + _diffuseColor + _specularColor;
	return _result;
}