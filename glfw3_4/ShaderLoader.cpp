#include "ShaderLoader.h"

using namespace std;

ShaderLoader::ShaderLoader() = default;


ShaderLoader::~ShaderLoader() {
	//unloadshader();
}

bool ShaderLoader::loadShaderSource(const string& filename, std::string& output) {

	std::ifstream file;
	char ch;
	file.open(filename.c_str());

	if (!file) {
		return false;
	}

	std::stringstream ss;

	ss << file.rdbuf();

	file.close();

	output = ss.str();



	this->len = ss.str().size();

	return true;
}


unsigned long ShaderLoader::GetLength() {
	return this->len;
}