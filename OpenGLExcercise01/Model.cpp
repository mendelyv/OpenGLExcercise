
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
	//std::cout << directory << std::endl;
	ProcessNode(scene->mRootNode, scene);
}


void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	//std::cout << node->mName.data << std::endl;
	//递归寻找Mesh节点
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(curMesh, scene));
	}

	//递归寻找模型的节点
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}


Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> tmpVertices;
	std::vector<unsigned int> tmpIndices;
	std::vector<Texture> tmpTextures;

	//循环处理aiMesh中的顶点
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0])
		{
			vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoord.x = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.texCoord = glm::vec2(0.0f, 0.0f);
		}
		tmpVertices.push_back(vertex);
	}

	//循环处理aiMesh中的indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			tmpIndices.push_back(face.mIndices[j]);
	}

	return Mesh(tmpVertices, tmpIndices, tmpTextures);
}

void Model::Draw(Shader* shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}