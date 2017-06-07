#version 330 core

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light
{
	vec3 position;

	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 eyePos;

varying vec3 FragPos;
varying vec3 Normal;

void main()
{
    // ambient
    vec3 ambient;
	ambient = light.ambient * material.ambient;

    // diffuse
    vec3 diffuse;
    vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diffuseFactor = max(0.0F, dot(normal, lightDir));
	diffuse = light.diffuse * (material.diffuse * diffuseFactor);

    // specular
    vec3 specular;
    vec3 fragPosToEye = normalize(eyePos - FragPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specularFactor = pow(max(0.0F, dot(fragPosToEye, reflectionDir)), material.shininess);
	specular = light.specular * (material.specular * specularFactor);

	gl_FragColor = vec4((ambient + diffuse + specular), 1.0F);
}