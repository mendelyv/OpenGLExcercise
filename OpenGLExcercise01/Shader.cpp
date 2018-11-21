#include "Shader.h"
#include <iostream>
#include <fstream>

using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFile;
	ifstream fragmentFile;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);
	
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
			throw exception("open file error");
	}
	catch (const exception& ex)
	{
		printf(ex.what());
	}
}

