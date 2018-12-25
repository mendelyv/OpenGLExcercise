#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
	vec3 lightDir = normalize(lightPos - FragPos);
	//漫反射光即为光线跟反射点的法向量点乘
	vec3 diffuse = dot(lightDir, Normal) * lightColor;
	FragColor = vec4((diffuse + ambientColor) * objColor, 1.0f);
}
