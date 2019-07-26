#ifndef PRISMMESH_H
#define PRISMMESH_H	

#include "Mesh.h"
#include <vector>
#include "CoreStructures.h"

struct PrismMesh : public Mesh {

	PrismMesh(int sides, float height, float radius);

private:

	void BuildMesh(int sides, float height, float radius);
	void AddVertex(float x, float y, float z);

private:

	std::vector<float> vertices_v;
	std::vector<unsigned int> indices_v;
};

#endif // !PRISMMESH_H
