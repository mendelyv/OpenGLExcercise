#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
//uniform vec4 ourColor;//从CPU输入的值
in vec2 texCoord;

uniform sampler2D tex;//外部输入一个纹理值
uniform sampler2D tex2;

void main()
{
   //FragColor = vertexColor;
   FragColor = mix(texture(tex, texCoord), texture(tex2, texCoord), 0.2);
}
