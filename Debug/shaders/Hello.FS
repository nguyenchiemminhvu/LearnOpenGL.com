#version 330 core

uniform vec3 eyePos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

varying vec3 FragPos;
varying vec3 Normal;

void main()
{
    // ambient
    vec3 ambient;
    float ambientFactor = 0.1F;
    ambient = lightColor * ambientFactor;

    // diffuse
    vec3 diffuse;
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuseFactor = max(0.0F, dot(lightDir, normal));
    diffuse = lightColor * diffuseFactor;

    // specular
    vec3 specular;
    float specularStrenth = 0.5F;
    vec3 fragPosToEye = normalize(eyePos - FragPos);
    vec3 reflectionDir = reflect(-lightDir, normal);
    float specularFactor = pow(max(0.0F, dot(fragPosToEye, reflectionDir)), 32);
    specular = lightColor * specularFactor * specularStrenth;

	gl_FragColor = vec4(objectColor * (ambient + diffuse + specular), 1.0F);
}