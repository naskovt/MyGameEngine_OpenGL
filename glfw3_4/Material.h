#ifndef MATERIAL_H
#define MATERIAL_H

#include "ShadersCreator.h"


class Material
{
public:
	Material() = delete;
	Material("shader.vert", "shader.frag");
	~Material();
private:
	ShadersCreator shader;
};

#endif

