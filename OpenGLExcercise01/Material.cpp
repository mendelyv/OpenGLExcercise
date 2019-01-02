
#include "Material.h"

Material::Material()
{

}

Material::Material(Shader* shader, unsigned int diffuse, unsigned int specular, unsigned int emission, glm::vec3 ambient, float shininess)
{
	this->shader = shader;
	this->diffuse = diffuse;
	this->specular = specular;
	this->emission = emission;
	this->ambient = ambient;
	this->shininess = shininess;
}

Material::~Material()
{

}