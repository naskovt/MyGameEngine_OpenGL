#ifndef  PYRAMIDMESH_H
#define PYRAMIDMESH_H

#include "Mesh.h"
#include <vector>
#include "CoreStructures.h"

class PyramidMesh :	public Mesh
{

public:
	PyramidMesh(int sides, float height, float radius);

private:

	void BuildMesh(int sides, float height, float radius);
	void AddVertex(float x, float y, float z);

private:

	std::vector<float> vertices_v;
	std::vector<unsigned int> indices_v;
};

#endif // ! PYRAMIDMESH_H
