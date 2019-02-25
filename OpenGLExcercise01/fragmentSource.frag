#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 texCoord;

struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct LightDirectional
{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
};

struct LightPoint
{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;

	float constant;
	float linear;
	float quadratic;
};

struct LightSpot
{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;

	float constant;
	float linear;
	float quadratic;

	float cosPhyInner;
	float cosPhyOutter;
};


uniform Material material;
//uniform LightPoint lightPoint;
//uniform LightSpot lightSpot;
uniform LightDirectional lightD;
uniform LightPoint lightP0;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightSpot lightS;


uniform vec3 objColor;
uniform vec3 ambientColor;
//uniform vec3 lightPos;
//uniform vec3 lightColor;
uniform vec3 cameraPos;
//uniform vec3 lightDirUniform;

//计算平行光的颜色
vec3 CalcLightDirectional(LightDirectional light, vec3 uNormal, vec3 dirToCamera)
{
	//diffuse max(dot(L, N), 0)
	float diffIntensity = max(dot(light.dirToLight, uNormal), 0);
	vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, texCoord).rgb;

	//specular pow(max((dot(R, Cam), 0),shininess)
	vec3 r = normalize(reflect(-light.dirToLight, uNormal));
	float specularInsensity = pow(max(dot(r, dirToCamera), 0), material.shininess);
	vec3 specColor = specularInsensity * light.color * texture(material.specular, texCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

//计算点光的颜色
vec3 CalcLightPoint(LightPoint light, vec3 uNormal, vec3 dirToCamera)
{
	//attenuation
	float dis = length(light.pos - FragPos);
	float attenuation = 1 / (light.constant + light.linear * dis + light.quadratic * (dis * dis));

	//diffuse
	float diffIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0) * attenuation;
	vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, texCoord).rgb;

	//specular
	vec3 r = normalize(reflect(-normalize(light.pos - FragPos), uNormal));
	float specularInsensity = pow(max(dot(r, dirToCamera), 0), material.shininess) * attenuation;
	vec3 specColor = specularInsensity * light.color * texture(material.specular, texCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

vec3 CalcLightSpot(LightSpot light, vec3 uNormal, vec3 dirToCamera)
{
	//attenuation
	float dis = length(light.pos - FragPos);
	float attenuation = 1 / (light.constant + light.linear * dis + light.quadratic * (dis * dis));
	float spotRatio;
	float cosTheta = dot(normalize(FragPos - light.pos), -light.dirToLight);
	if(cosTheta > light.cosPhyInner)
	{
		spotRatio = 1;
	}
	else if(cosTheta > light.cosPhyOutter)
	{
		spotRatio = (cosTheta - light.cosPhyOutter) / (light.cosPhyInner - light.cosPhyOutter);
	}
	else
	{
		spotRatio = 0;
	}

	//diffuse
	float diffIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0) * attenuation * spotRatio;
	vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, texCoord).rgb;

	//specular
	vec3 r = normalize(reflect(-normalize(light.pos - FragPos), uNormal));
	float specularInsensity = pow(max(dot(r, dirToCamera), 0), material.shininess) * attenuation;
	vec3 specColor = specularInsensity * light.color * texture(material.specular, texCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

void main()
{
	vec3 uNormal = normalize(Normal);
	vec3 finalResult = vec3(0, 0, 0);
	vec3 dirToCamera = normalize(cameraPos - FragPos);

	finalResult += CalcLightDirectional(lightD, uNormal, dirToCamera);

	finalResult += CalcLightPoint(lightP0, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP1, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP2, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP3, uNormal, dirToCamera);

	finalResult += CalcLightSpot(lightS, uNormal, dirToCamera);
	
	FragColor = vec4(finalResult, 1.0f);	
}
