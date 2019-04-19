#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>


class ShaderLoader
{
public:
	ShaderLoader();
	~ShaderLoader();


	bool loadShaderSource(const std::string& filename, std::string& output);

	unsigned long GetLength();


private:
	unsigned long len;

};

#endif // !SHADERLOADER_H
