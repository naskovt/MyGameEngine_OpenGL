#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "CoreStructures.h"
#include "Shader.h"

class Material
{
public:
	Material() = delete;
	Material(Shader& shader, float r, float g, float b, float a);

	float _color[4];
	Shader& GetShader();

	~Material();
private:
	Shader& _shader;

};

#endif

