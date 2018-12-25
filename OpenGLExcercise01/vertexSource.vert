#version 330 core
layout(location = 4) in vec3 aPos;//这里的管线要跟下方使用的管线编号相同
layout(location = 7) in vec3 aNormal;//法向量

//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 FragPos;
out vec3 Normal;
void main()
{
	gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
	Normal = mat3(modelMat) * aNormal;
}