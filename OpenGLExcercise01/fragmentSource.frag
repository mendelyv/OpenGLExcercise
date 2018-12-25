#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
//uniform vec4 ourColor;//从CPU输入的值
in vec2 texCoord;

uniform sampler2D tex;//外部输入一个纹理值
uniform sampler2D tex2;
uniform vec3 objColor;
uniform vec3 ambientColor;

void main()
{
//	FragColor = mix(texture(tex, texCoord), texture(tex2, texCoord), 0.2);
	//这里的向量相乘是图学语言实现的，即为返回向量的对应元素相乘后的一个新的向量
	FragColor = vec4(objColor * ambientColor, 1.0f) * mix(texture(tex, texCoord), texture(tex2, texCoord), 0.2);
}
