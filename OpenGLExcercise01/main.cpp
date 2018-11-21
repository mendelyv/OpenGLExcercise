
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

//顶点
float vertices[] = {
	-0.5f,-0.5f,0.0f, 1.0f,0.0f,0.0f,
	0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
	0.0f,0.5f,0.0f, 0.0f,0.0f,1.0f
};

const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 4) in vec3 aPos;\n"//这里的管线要跟下方使用的管线编号相同
"layout(location = 5) in vec3 aColor;\n"
"out vec4 vertexColor;\n"//向片段着色器输出一个颜色
"void main(){\n"
"     gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"	  vertexColor = vec4(aColor.x,aColor.y,aColor.z,1.0); \n"
"}\n";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"uniform vec4 ourColor;\n"//从CPU输入的值
"void main(){\n"
"   FragColor = vertexColor;\n"
"}";

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	Shader* shader = new Shader("vertexSource.txt", "fragmentSource.txt");

	//printf("hihihi\n");
	//system("pause");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//告诉GLFW要用的主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//子版版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//渲染管线的流程

	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
	if (window == NULL)
	{
		printf("Open Window Failed");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	//Init GLEW
	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW Failed");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);

	//顶点数组对象：Vertex Array Object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//顶点缓冲对象：Vertex Buffer Object
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//位置属性
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(4);

	//颜色属性
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(5);

	//如果不关闭窗口就一直交换缓冲区
	while (!glfwWindowShouldClose(window))
	{
		//input commands
		processInput(window);

		// rendering commands here
		glClearColor(0, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2 + 0.5;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0, greenValue, 0, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}

