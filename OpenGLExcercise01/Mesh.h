#pragma once

#ifndef __MESH_H__
#define __MESH_H__

#include <glm.hpp>
#include <string>
#include <vector>

#include "Shader.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};


class Mesh 
{
public :
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

public :
	Mesh(float vectices[]);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh();

	void Draw(Shader *shader);

private:
	unsigned int VAO, VBO, EBO;
	void SetupMesh();
};


#endif
