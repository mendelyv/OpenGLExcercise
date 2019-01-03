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

struct LightPoint
{
	float constant;
	float linear;
	float quadratic;
};

uniform Material material;
uniform LightPoint lightPoint;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform vec3 lightDirUniform;

void main()
{
	float dis = length(lightPos - FragPos);
	float attenuation = 1.0 / (lightPoint.constant + lightPoint.linear * dis + lightPoint.quadratic * (dis * dis));

	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 reflectVec = reflect(-lightDir, Normal);
	vec3 cameraVec = normalize(cameraPos - FragPos);

	float specularAmount = pow(max(dot(reflectVec, cameraVec), 0), material.shininess);
	vec3 specular = texture(material.specular, texCoord).rgb * specularAmount * lightColor;

	//漫反射光即为光线跟反射点的法向量点乘
	vec3 diffuse = texture(material.diffuse, texCoord).rgb * max(dot(lightDir, Normal), 0) * lightColor;
//	vec3 diffuse = texture(material.diffuse, texCoord).rgb;
	vec3 ambient = ambientColor * texture(material.diffuse, texCoord).rgb;
	FragColor = vec4((ambient + (specular + diffuse) * attenuation) * objColor, 1.0f);
}
