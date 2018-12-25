#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

void main()
{
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 reflectVec = reflect(-lightDir, Normal);
	vec3 cameraVec = normalize(cameraPos - FragPos);

	float specularAmount = pow(max(dot(reflectVec, cameraVec), 0), 32);
	vec3 specular = specularAmount * lightColor;

	//漫反射光即为光线跟反射点的法向量点乘
	vec3 diffuse = max(dot(lightDir, Normal), 0) * lightColor;
	FragColor = vec4((diffuse + ambientColor + specular) * objColor, 1.0f);
}
