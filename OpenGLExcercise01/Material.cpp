
#include "Material.h"

Material::Material()
{

}

Material::Material(Shader* shader, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 ambient, float shininess)
{
	this->shader = shader;
	this->diffuse = diffuse;
	this->specular = specular;
	this->ambient = ambient;
	this->shininess = shininess;
}

Material::~Material()
{

}