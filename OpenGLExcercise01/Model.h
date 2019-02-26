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

class Model
{
public:
	Model(std::string const &path);
	~Model();

	std::vector<Mesh> meshs;
	std::string directory;

private:
	void LoadModel(std::string const &path);
};

#endif
