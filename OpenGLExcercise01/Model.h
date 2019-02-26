#pragma once

#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

#include "Mesh.h"
#include "Shader.h"

class Model
{
public:
	Model(std::string const &path);
	~Model();

	std::vector<Mesh> meshes;
	std::string directory;

	void Draw(Shader* shader);

private:
	void LoadModel(std::string const &path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

#endif
