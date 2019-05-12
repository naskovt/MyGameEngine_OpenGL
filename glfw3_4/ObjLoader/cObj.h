#pragma once
#include <vector>
#include <string>
#include "MeshStructures.h"

class cObj {
private:
	//GLuint list;
protected:
public:
	std::vector<vertex> vertices;
	std::vector<vertex> texcoords;
	std::vector<vertex> normals;
	std::vector<vertex> parameters;
	std::vector<face> faces;


	cObj() = default;
	cObj(std::string filename);

	//~cObj();

	//void compileList();
	//void render();
};
