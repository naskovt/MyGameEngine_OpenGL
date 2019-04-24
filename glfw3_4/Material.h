#ifndef MATERIAL_H
#define MATERIAL_H

#include "ShadersCreator.h"


class Material
{
public:
	Material() = delete;
	Material(std::string vertShaderName, std::string fragShaderName);
	~Material();
private:
	ShadersCreator _shader;
};

#endif

