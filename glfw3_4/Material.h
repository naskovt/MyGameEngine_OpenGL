#ifndef MATERIAL_H
#define MATERIAL_H

#include "ShadersCreator.h"
#include <glm/glm.hpp>


class Material
{
public:
	Material() = delete;
	Material(ShadersCreator& shader, float r, float g, float b, float a);

	float _color[4];
	ShadersCreator& GetShader();

	~Material();
private:
	ShadersCreator& _shader;
};

#endif

