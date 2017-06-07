#version 330 core

/*
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
*/

struct Material
{
    sampler2D	diffuse;
    sampler2D	specular;
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
vec3 calculateDirectionalLights();
vec3 calculatePointLights();
vec3 calculateFlashLights();

void main()
{
	vec3 result;

	// turn flash light on or off
	if(isFlashLightOn == 1)
	{
		result = calculateFlashLights();
	}
	else if(isFlashLightOn == 0)
	{
		result = calculateDirectionalLights();
		result += calculatePointLights();
	}

	gl_FragColor = vec4(result, 1.0f);
}


vec3 calculateDirectionalLights()
{
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	// -------------------------------------------
	// ambient
	ambient = theSun.ambient * vec3(texture(material.diffuse, UV));

	// -------------------------------------------
	// diffuse
	vec3 normal = normalize(Normal);
	float diffuseFactor = max(0.0f, dot(-theSun.direction, normal));
	diffuse = theSun.diffuse * diffuseFactor * vec3(texture(material.diffuse, UV));

	// -------------------------------------------
	// specular
	vec3 fromFragToEye = normalize(eyePos - FragPos);
	vec3 reflectionDir = reflect(theSun.direction, normal);
	float specularFactor = pow(max(0.0f, dot(fromFragToEye, reflectionDir)), material.shininess);
	specular = theSun.specular * specularFactor * vec3(texture(material.specular, UV));

	return vec3(ambient + diffuse + specular);
}


vec3 calculatePointLights()
{
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	// -------------------------------------------
	// ambient
	ambient = roundLamp.ambient * vec3(texture(material.diffuse, UV));

	// -------------------------------------------
	// diffuse
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(roundLamp.position - FragPos);
	float diffuseFactor = max(0.0F, dot(lightDir, normal));
	diffuse = roundLamp.diffuse * diffuseFactor * vec3(texture(material.diffuse, UV));

	// -------------------------------------------
	// specular
	vec3 fromFragToEye = normalize(eyePos - FragPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specularFactor = pow(max(0.0f, dot(fromFragToEye, reflectionDir)), material.shininess);
	specular = roundLamp.specular * specularFactor * vec3(texture(material.specular, UV));

	// -------------------------------------------
	// calculate attenuation
	float d = length(roundLamp.position - FragPos);
	float attenuation = 1.0f / (roundLamp.constant + roundLamp.linear * d + roundLamp.quadratic * d * d);
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}


vec3 calculateFlashLights()
{
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	// -------------------------------------------
	// ambient
	ambient = flashLight.ambient * vec3(texture(material.diffuse, UV));

	// -------------------------------------------
	// diffuse
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(flashLight.direction);
	float diffuseFactor = max(0.0F, dot(-lightDir, normal));
	diffuse = flashLight.diffuse * diffuseFactor * vec3(texture(material.diffuse, UV));

	// -------------------------------------------
	// specular
	vec3 fromFragToEye = normalize(eyePos - FragPos);
	vec3 reflectionDir = reflect(lightDir, normal);
	float specularFactor = pow(max(0.0f, dot(fromFragToEye, reflectionDir)), material.shininess);
	specular = flashLight.specular * specularFactor * vec3(texture(material.specular, UV));

	// -------------------------------------------
	// calculate attenuation
	float d = length(flashLight.position - FragPos);
	float attenuation = 1.0F / (flashLight.constant + flashLight.linear * d + flashLight.quadratic * d * d);
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	/*
		// smooth/soft flash light edges
		// intensity = (theta - outer) / epsilon;
	*/
	// -------------------------------------------
	// theta
	vec3 fromLightToFrag = normalize(FragPos - flashLight.position);
	float theta = dot(fromLightToFrag, normalize(flashLight.direction));
	float epsilon = flashLight.cutOff - flashLight.cutOffOuter;
	float intensity = clamp((theta - flashLight.cutOffOuter) / epsilon , 0.0f, 1.0f);
	ambient *= intensity;
	diffuse *= intensity;
	specular *= intensity;

	return (ambient + diffuse + specular);
}
