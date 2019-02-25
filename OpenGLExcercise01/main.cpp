
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"
#include "Material.h"
#include "Camera.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Mesh.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#pragma region Model Data
//顶点
//float vertices[] = {
//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//
//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//};

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion

//Instantiate Camera Object
Camera* camera = new Camera(glm::vec3(0, 0, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));

//Instantiate Light Object
LightDirectional* lightD = new LightDirectional(
	glm::vec3(1.0f, 1.0f, -1.0f), 
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0)
);

LightPoint* lightP0 = new LightPoint(glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(1.0f, 0.0f, 0.0f)
);
LightPoint* lightP1 = new LightPoint(glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(0.0f, 1.0f, 0.0f)
);
LightPoint* lightP2 = new LightPoint(glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(0.0f, 0.0f, 1.0f)
);
LightPoint* lightP3 = new LightPoint(glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(1.0f, 1.0f, 1.0f)
);

LightSpot* lightS = new LightSpot(glm::vec3(0.0f, 5.0f, 0.0f),
	glm::vec3(glm::radians(90.0f), 0.0f, 0.0f),
	glm::vec3(1.0f, 1.0f, 1.0f)
);

//LightSpot* light = new LightSpot(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(glm::radians(90.0f), 0, 0));

#pragma region Input Declare
//检测输入信号
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->forwardSpeed = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->forwardSpeed = -1.0f;
	}
	else
	{
		camera->forwardSpeed = 0.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->rightSpeed = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->rightSpeed = -1.0f;
	}
	else
	{
		camera->rightSpeed = 0.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera->upSpeed = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera->upSpeed = -1.0f;
	}
	else
	{
		camera->upSpeed = 0.0f;
	}
}

double lastX;
double lastY;
bool firstMouse = true;//避免首次进入时鼠标的数字过大

//鼠标事件回调
void mouseEventCallBack(GLFWwindow* window, double x, double y)
{
	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}
	double deltaX, deltaY;
	deltaX = lastX - x;
	deltaY = lastY - y;

	camera->ProcessMouseMovement(deltaX, deltaY);
	lastX = x;
	lastY = y;
}
#pragma endregion

//加载纹理给GPU
unsigned int LoadImageToGPU(const char* imageName, int textureSlot, bool hasAlpha = false)
{
	stbi_set_flip_vertically_on_load(true);//反转y轴
	unsigned int ret;
	int width, height, numChannel;
	glGenTextures(1, &ret);
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, ret);
	unsigned char* data = stbi_load(imageName, &width, &height, &numChannel, 0);
	if (data)
	{
		if(!hasAlpha)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("load image failed \n");
	}
	stbi_image_free(data);
	return ret;
}



int main()
{
	#pragma region Open a Window
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
	//隐藏鼠标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseEventCallBack);

	//Init GLEW
	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW Failed");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//开启线框模式
	glEnable(GL_DEPTH_TEST);//开启深度测试
	#pragma endregion

	Shader* shader = new Shader("vertexSource.vert", "fragmentSource.frag");
	Material* material = new Material(shader, LoadImageToGPU("container2.png", Shader::DIFFUSE, true), LoadImageToGPU("container2_specular.png", Shader::SPECULAR, true), glm::vec3(1.0f, 1.0f, 1.0f), 64.0f);

	#pragma region Init VAO,VBO
	Mesh *cube = new Mesh(vertices);
	////顶点数组对象：Vertex Array Object
	//unsigned int VAO;
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

	////顶点缓冲对象：Vertex Buffer Object
	//unsigned int VBO;
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	////索引缓冲对象：Element Buffer Object
	////unsigned int EBO;
	////glGenBuffers(1, &EBO);
	////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	////glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_READ);

	////位置属性
	//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(4);

	////颜色属性
	////glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	////glEnableVertexAttribArray(5);

	////文理uv属性
	////glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	////glEnableVertexAttribArray(6);

	////法向量属性
	//glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(7);

	////uv属性
	//glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(8);

	#pragma endregion

	stbi_set_flip_vertically_on_load(true);//反转y轴

	//纹理缓存
	//unsigned int texBufferA;
	//texBufferA = LoadImageToGPU("container.jpg", 0);
	//unsigned int texBufferB;
	//texBufferB = LoadImageToGPU("awesomeface.png", 3, true);

	//计算位移坐标矩阵
	//tip : 当要混合操作时，先进行缩放操作，然后是旋转，最后是位移，否则它们会（消极的）相互影响
	//tip : 列主序需要从右往左阅读，但是计算时要从左往右
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(-1.0f, 0, 0));//位移
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0, 0, 1.0f));//旋转
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));//缩放

	//计算坐标转换所需要的矩阵，MVP矩阵
	glm::mat4 modelMat;//LOCATION MATRIX
	//modelMat = glm::rotate(modelMat, glm::radians(-45.0f), glm::vec3(1.0f, 1.0f, 0));
	glm::mat4 viewMat;//VIEW MATRIX
	viewMat = camera->GetViewMatrix();
	glm::mat4 projMat;
	//PROJECTION MATRIX转换，视椎体夹角，屏幕宽高比，最近，最远
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	shader->Use();
	//glUniform1i(glGetUniformLocation(shader->ID, "tex"), 0);
	//glUniform1i(glGetUniformLocation(shader->ID, "tex2"), 3);
	//glUniformMatrix4fv(glGetUniformLocation(shader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
	//如果不关闭窗口就一直交换缓冲区
	while (!glfwWindowShouldClose(window))//render loop
	{
		//input commands
		processInput(window);

		// rendering commands here
		//glClearColor(0, 0.5f, 0.5f, 1.0f);
		glClearColor(0, 0, 0, 1.0f);
		//清除颜色buffer和深度buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		viewMat = camera->GetViewMatrix();
		for (int i = 0; i < 1; i++)
		{
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, texBufferA);
			//glActiveTexture(GL_TEXTURE3);
			//glBindTexture(GL_TEXTURE_2D, texBufferB);
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			glUniform3f(glGetUniformLocation(shader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(shader->ID, "ambientColor"), 0.1f, 0.1f, 0.1f);
			
			glUniform3f(glGetUniformLocation(shader->ID, "lightD.pos"), lightD->position.x, lightD->position.y, lightD->position.z);
			glUniform3f(glGetUniformLocation(shader->ID, "lightD.color"), lightD->color.x, lightD->color.y, lightD->color.z);
			glUniform3f(glGetUniformLocation(shader->ID, "lightD.dirToLight"), lightD->direction.x, lightD->direction.y, lightD->direction.z);
			
			glUniform3f(glGetUniformLocation(shader->ID, "lightP0.pos"), lightP0->position.x, lightP0->position.y, lightP0->position.z);
			glUniform3f(glGetUniformLocation(shader->ID, "lightP0.color"), lightP0->color.x, lightP0->color.y, lightP0->color.z);
			glUniform3f(glGetUniformLocation(shader->ID, "lightP0.dirToLight"), lightP0->direction.x, lightP0->direction.y, lightP0->direction.z);
			glUniform1f(glGetUniformLocation(shader->ID, "lightP0.constant"), lightP0->constant);
			glUniform1f(glGetUniformLocation(shader->ID, "lightP0.linear"), lightP0->linear);
			glUniform1f(glGetUniformLocation(shader->ID, "lightP0.quadratic"), lightP0->quadratic);

			glUniform3f(glGetUniformLocation(shader->ID, "lightP1.pos"), lightP1->position.x, lightP1->position.y, lightP1->position.z);
			glUniform3f(glGetUniformLocation(shader->ID, "lightP1.color"), lightP1->color.x, lightP1->color.y, lightP1->color.z);
			glUniform3f(glGetUniformLocation(shader->ID, "lightP1.dirToLight"), lightP1->direction.x, lightP1->direction.y, lightP1->direction.z);
			glUniform1f(glGetUniformLocation(shader->ID, "lightP1.constant"), lightP1->constant);
			glUniform1f(glGetUniformLocation(shader->ID, "lightP1.linear"), lightP1->linear);
			glUniform1f(glGetUniformLocation(shader->ID, "lightP1.quadratic"), lightP1->quadratic);

			glUniform3f(glGetUniformLocation(shader->ID, "lightP2.pos"), lightP2->position.x, lightP2->position.y, lightP2->position.z);
			glUniform3f(glGetUniformLocation(shader->ID, "lightP2.color"), lightP2->color.x, lightP2->color.y, lightP2->color.z);
			glUniform3f(glGetUniformLocation(shader->ID, "lightP2.dirToLight"), lightP2->direction.x, lightP2->direction.y, lightP2->direction.z);
			glUniform1f(glGetUniformLocation(shader->ID, "lightP2.constant"), lightP2->constant);
			glUniform1f(glGetUniformLocation(shader->ID, "lightP2.linear"), lightP2->linear);
			glUniform1f(glGetUniformLocation(shader->ID, "lightP2.quadratic"), lightP2->quadratic);

			glUniform3f(glGetUniformLocation(shader->ID, "lightP3.pos"), lightP3->position.x, lightP3->position.y, lightP3->position.z);
			glUniform3f(glGetUniformLocation(shader->ID, "lightP3.color"), lightP3->color.x, lightP3->color.y, lightP3->color.z);
			glUniform3f(glGetUniformLocation(shader->ID, "lightP3.dirToLight"), lightP3->direction.x, lightP3->direction.y, lightP3->direction.z);
			glUniform1f(glGetUniformLocation(shader->ID, "lightP3.constant"), lightP3->constant);
			glUniform1f(glGetUniformLocation(shader->ID, "lightP3.linear"), lightP3->linear);
			glUniform1f(glGetUniformLocation(shader->ID, "lightP3.quadratic"), lightP3->quadratic);

			glUniform3f(glGetUniformLocation(shader->ID, "lightS.pos"), lightS->position.x, lightS->position.y, lightS->position.z);
			glUniform3f(glGetUniformLocation(shader->ID, "lightS.color"), lightS->color.x, lightS->color.y, lightS->color.z);
			glUniform3f(glGetUniformLocation(shader->ID, "lightS.dirToLight"), lightS->direction.x, lightS->direction.y, lightS->direction.z);
			glUniform1f(glGetUniformLocation(shader->ID, "lightS.constant"), lightS->constant);
			glUniform1f(glGetUniformLocation(shader->ID, "lightS.linear"), lightS->linear);
			glUniform1f(glGetUniformLocation(shader->ID, "lightS.quadratic"), lightS->quadratic);
			glUniform1f(glGetUniformLocation(shader->ID, "lightS.cosPhyInner"), lightS->cosPhyInner);
			glUniform1f(glGetUniformLocation(shader->ID, "lightS.cosPhyOutter"), lightS->cosPhyOutter);
			
			glUniform3f(glGetUniformLocation(shader->ID, "cameraPos"), camera->position.x, camera->position.y, camera->position.z);
			//glUniform1f(glGetUniformLocation(shader->ID, "lightPoint.constant"), light->constant);
			//glUniform1f(glGetUniformLocation(shader->ID, "lightPoint.linear"), light->linear);
			//glUniform1f(glGetUniformLocation(shader->ID, "lightPoint.quadratic"), light->quadratic);
			material->shader->SetUniform3f("material.ambient", material->ambient);
			//material->shader->SetUniform1f("material.diffuse", material->diffuse);
			material->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
			material->shader->SetUniform1i("material.specular", Shader::SPECULAR);
			//material->shader->SetUniform3f("material.specular", material->specular);
			material->shader->SetUniform1f("material.shininess", material->shininess);

			cube->Draw(material->shader);
			//glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);//交换双缓冲
		glfwPollEvents();//获取输入
		camera->UpdateCameraPosition();//更新摄像机位置
	}

	glfwTerminate();
	return 0;

}