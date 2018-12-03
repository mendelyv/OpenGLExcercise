#ifndef __SHADER_H__
#define __SHADER_H__
#include <string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID; //Shader Program ID;

public:
	void Use();


private:
	void CheckCompileErrors(unsigned int ID, std::string type);
};

#endif
