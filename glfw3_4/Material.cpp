#include "Material.h"



Material::Material(Shader& shader, float r, float g, float b, float a) :
	_shader(shader), _color{ r,g,b,a } {};

Shader& Material::GetShader() {
	return this->_shader;
}

Material::~Material()
{
}
