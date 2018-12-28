#version 330 core
layout(location = 4) in vec3 aPos;//这里的管线要跟下方使用的管线编号相同
layout(location = 7) in vec3 aNormal;//法向量
layout(location = 8) in vec2 aTexCoord;

//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 FragPos;
out vec3 Normal;
out vec2 texCoord;

void main()
{
	gl_Position = projMat * viewMat * modelMat * vec4(aPos.xyz, 1.0f);
	FragPos = (modelMat * vec4(aPos.xyz, 1.0f)).xyz;
	texCoord = aTexCoord;
	Normal = mat3(transpose(inverse(modelMat))) * aNormal;
}