#ifndef CORE_STRUCTURES_H
#define CORE_STRUCTURES_H

#include <string>
#include <glm/glm.hpp>
#include "Enumerators.h"

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	//TextureType type;
	std::string type;
	std::string name;
	std::string path;
};

#endif // CORE_STRUCTURES_H

