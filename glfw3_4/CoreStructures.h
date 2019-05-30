#ifndef CORE_STRUCTURES_H
#define CORE_STRUCTURES_H

#include <string>
#include <glm/glm.hpp>
#include "Enumerators.h"

struct PVM_Matrix {

	PVM_Matrix(glm::mat4 P, glm::mat4 V, glm::mat4 M) : Projection(P),View(V),Model(M) {};

	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 Model;
};

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;

	//Texture type, used when checking which uniform variable to set in the shader drawing method;
	std::string type;

	std::string name;
	std::string path;
};

#endif // CORE_STRUCTURES_H

