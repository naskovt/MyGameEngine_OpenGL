#include "Material.h"



Material::Material(ShadersCreator& shader, float r, float g, float b, float a) :
	_shader(shader), _color{ r,g,b,a } {};

ShadersCreator& Material::GetShader() {
	return this->_shader;
}

Material::~Material()
{
}
