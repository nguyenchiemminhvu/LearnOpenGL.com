#version 330 core

/*
	// ------------------------------------------------
	// Attenuation use for point light or flash light
	F(attenuation) = 1.0F / ( Kq * d * d + Kl * d + Kc );
	
	// ------------------------------------------------
	// Choose the proper values
	Distance	Constant	Linear	Quadratic
	7			1.0			0.7		1.8
	13			1.0			0.35	0.44
	20			1.0			0.22	0.20
	32			1.0			0.14	0.07
	50			1.0			0.09	0.032
	65			1.0			0.07	0.017
	100			1.0			0.045	0.0075
	160			1.0			0.027	0.0028
	200			1.0			0.022	0.0019
	325			1.0			0.014	0.0007
	600			1.0			0.007	0.0002
	3250		1.0			0.0014	0.000007
	// ------------------------------------------------

	// ------------------------------------------------
	// smooth/soft flash light edges
	intensity = (theta - outer) / epsilon;
*/


struct Material
{
    sampler2D texture_diffuse1;
	sampler2D texture_specular1;
    float		shininess;
}; 

struct DirectionalLight
{
	vec3 direction;

	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
	vec3 position;

	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	// ------------------------
	// attenuation
	float quadratic;
	float linear;
	float constant;
};

struct FlashLight
{
	vec3 position;
	vec3 direction;
	float cutOff;
	float cutOffOuter;

	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	// ------------------------
	// attenuation
	float quadratic;
	float linear;
	float constant;
};

// -------------------------------------------
// Directional light begin
uniform DirectionalLight theSun;

// -------------------------------------------
// Point light
uniform PointLight roundLamp;

// -------------------------------------------
// Flash light
uniform FlashLight flashLight;

// -------------------------------------------
// varying variables
varying vec3 FragPos;
varying vec3 Normal;
varying vec2 UV;

// -------------------------------------------
// others
uniform Material material;
uniform vec3 eyePos;
uniform int isFlashLightOn;

// -------------------------------------------
// calculate light functions
vec3 calculateDirectionalLights(in DirectionalLight light, in vec3 normal, in vec3 fromFragToEye);
vec3 calculatePointLights(in PointLight light, in vec3 normal, in vec3 fromFragToEye);
vec3 calculateFlashLights(in FlashLight light, in vec3 normal, in vec3 fromFragToEye);

float linearizeDepth(float depth);

float near = 0.1;
float far = 200.0;


void main()
{
	vec3 result;

	// inputs
	vec3 normal = normalize(Normal);
	vec3 fromFragToEye = normalize(eyePos - FragPos);

	// turn flash light on or off
	if(isFlashLightOn == 1)
	{
		result = calculateDirectionalLights(theSun, normal, fromFragToEye);
		result += calculateFlashLights(flashLight, normal, fromFragToEye);
	}
	else if(isFlashLightOn == 0)
	{
		result = calculateDirectionalLights(theSun, normal, fromFragToEye);
		result += calculatePointLights(roundLamp, normal, fromFragToEye);
	}

	// linearize depth
	float depth = linearizeDepth(gl_FragCoord.z) / far;

	gl_FragColor = vec4(vec3(clamp(depth, 0.0f, 0.3f)) + result, 1.0f);
}


vec3 calculateDirectionalLights(in DirectionalLight light, in vec3 normal, in vec3 fromFragToEye)
{
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	// -------------------------------------------
	// ambient
	ambient = light.ambient * vec3(texture(material.texture_diffuse1, UV));

	// -------------------------------------------
	// diffuse
	float diffuseFactor = max(0.0f, dot(-light.direction, normal));
	diffuse = light.diffuse * diffuseFactor * vec3(texture(material.texture_diffuse1, UV));

	// -------------------------------------------
	// specular
	//vec3 reflectionDir = reflect(theSun.direction, normal);
	//float specularFactor = pow(max(0.0f, dot(fromFragToEye, reflectionDir)), material.shininess);
	//specular = light.specular * specularFactor * vec3(texture(material.texture_specular1, UV));

	return vec3(ambient + diffuse + specular);
}


vec3 calculatePointLights(in PointLight light, in vec3 normal, in vec3 fromFragToEye)
{
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	// -------------------------------------------
	// ambient
	ambient = light.ambient * vec3(texture(material.texture_diffuse1, UV));

	// -------------------------------------------
	// diffuse
	vec3 lightDir = normalize(light.position - FragPos);
	float diffuseFactor = max(0.0F, dot(lightDir, normal));
	diffuse = light.diffuse * diffuseFactor * vec3(texture(material.texture_diffuse1, UV));

	// -------------------------------------------
	// specular
	//vec3 reflectionDir = reflect(-lightDir, normal);
	//float specularFactor = pow(max(0.0f, dot(fromFragToEye, reflectionDir)), material.shininess);
	//specular = light.specular * specularFactor * vec3(texture(material.texture_specular1, UV));

	// -------------------------------------------
	// calculate attenuation
	float d = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * d + light.quadratic * d * d);
	ambient *= attenuation;
	diffuse *= attenuation;
	//specular *= attenuation;

	return (ambient + diffuse);
}


vec3 calculateFlashLights(in FlashLight light, in vec3 normal, in vec3 fromFragToEye)
{
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	// -------------------------------------------
	// ambient
	ambient = light.ambient * vec3(texture(material.texture_diffuse1, UV));

	// -------------------------------------------
	// diffuse
	vec3 lightDir = normalize(flashLight.direction);
	float diffuseFactor = max(0.0F, dot(-lightDir, normal));
	diffuse = light.diffuse * diffuseFactor * vec3(texture(material.texture_diffuse1, UV));

	// -------------------------------------------
	// specular
	//vec3 reflectionDir = reflect(lightDir, normal);
	//float specularFactor = pow(max(0.0f, dot(fromFragToEye, reflectionDir)), material.shininess);
	//specular = light.specular * specularFactor * vec3(texture(material.texture_specular1, UV));

	// -------------------------------------------
	// calculate attenuation
	float d = length(light.position - FragPos);
	float attenuation = 1.0F / (light.constant + light.linear * d + light.quadratic * d * d);
	ambient *= attenuation;
	diffuse *= attenuation;
	//specular *= attenuation;

	// -------------------------------------------
	// theta
	vec3 fromLightToFrag = normalize(FragPos - light.position);
	float theta = dot(fromLightToFrag, normalize(light.direction));
	float epsilon = light.cutOff - light.cutOffOuter;
	float intensity = clamp((theta - light.cutOffOuter) / epsilon , 0.0f, 1.0f);
	ambient *= intensity;
	diffuse *= intensity;
	//specular *= intensity;

	return (ambient + diffuse);
}


float linearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0;
	return (2.0 * near * far) / (far + near - z * (far - near));
}