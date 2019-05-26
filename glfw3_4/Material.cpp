#include "Material.h"

Material::Material(Shader& shader) :
	_shader(shader), _color{ 0,0,0,1 } {};

Material::Material(Shader& shader, std::vector<Texture*> textures_v) :
	_shader(shader), _color{ 0,0,0,1 }, _textures_v(textures_v) {};

Material::Material(Shader& shader, float r, float g, float b, float a) :
	_shader(shader), _color{ r,g,b,a } {};

Shader& Material::GetShader() {
	return this->_shader;
}

Material::~Material()
{
}
