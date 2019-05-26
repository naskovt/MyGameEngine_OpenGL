#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <vector>

#include "CoreStructures.h"
#include "Shader.h"

class Material
{
public:
	std::vector<Texture*> _textures_v;
	float _color[4];

	Material() = delete;
	Material(Shader& shader);
	Material(Shader& shader, std::vector<Texture*> textures_v);
	Material(Shader& shader, float r, float g, float b, float a);

	Shader& GetShader();

	~Material();
private:

	Shader& _shader;


};

#endif

