
#include "Model.h"

Model::Model(std::string const &path)
{
	LoadModel(path);
}

Model::~Model()
{

}

void Model::LoadModel(std::string const &path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "MODEL FILE ERROR" << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('\\'));
	std::cout << directory << std::endl;
}