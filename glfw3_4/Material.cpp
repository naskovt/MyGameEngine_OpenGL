#include "Material.h"



Material::Material(std::string vertShaderName, std::string fragShaderName) : _shader("shader.vert", "shader.frag")
{
}



Material::~Material()
{
}
