#ifndef MESH_H
#define MESH_H

class Mesh {
public:
	float* vertices;
	unsigned int* indices;

	unsigned int indicesSize;
	unsigned int verticesSize;

	Mesh() : vertices(nullptr), indices(nullptr), indicesSize(0), verticesSize(0) {};

};
#endif
