#pragma once

class Mesh {
public:
	float* vertices;
	unsigned int* indices;

	unsigned int indicesSize;
	unsigned int verticesSize;

	Mesh() : vertices(nullptr), indices(nullptr), indicesSize(0), verticesSize(0) {};

};

//class Mesh {
//	virtual unsigned int* getIndexBuffer(unsigned int *size) = 0;
//	virtual unsigned int* getVertexBuffer(unsigned int* size) = 0;
//};
