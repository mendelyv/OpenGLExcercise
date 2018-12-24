#version 330 core
layout(location = 4) in vec3 aPos;//这里的管线要跟下方使用的管线编号相同
layout(location = 5) in vec3 aColor;
layout(location = 6) in vec2 aTexCoord;//uv值

//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec4 vertexColor;//向片段着色器输出一个颜色
out vec2 texCoord;
void main()
{
	gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
	vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);
	texCoord = aTexCoord;
}