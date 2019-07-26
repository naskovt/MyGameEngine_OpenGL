#include "PyramidMesh.h"

PyramidMesh::PyramidMesh(int sides = 3, float height = 1, float radius = 1) {

	BuildMesh((sides < 3) ? 3 : sides, height, abs(radius));

	// assign vertices and indices
	Mesh::LoadDataToMeshArrays(vertices_v, indices_v);
}

void PyramidMesh::BuildMesh(int sides, float height, float radius) {

	// build face
	Vector3 lastVertex;
	Vector3 currentVertex;
	const float sidesAngle = 360 / sides;


	const float capHeight = -(height / 2);

	// first add a centered vertex of the face/cap 
	AddVertex(0, -capHeight, 0);

	for (int i = 0; i < sides; i++)
	{
		if (i == 0)
		{
			currentVertex.x = 0;
			currentVertex.z = radius;
		}
		else
		{
			Mesh::RotatePointUpAxis(lastVertex, currentVertex, sidesAngle);
		}

		currentVertex.y = capHeight;

		AddVertex(currentVertex.x, capHeight, currentVertex.z);

		lastVertex = currentVertex;

		if (i > 0)
		{
			// next triangle, anticlockwise
			indices_v.push_back(0);
			indices_v.push_back(i);
			indices_v.push_back(i + 1);
		}

		if (i + 1 == sides)
		{
			// the last triangle, connected to the first indices
			indices_v.push_back(0);
			indices_v.push_back(i + 1);
			indices_v.push_back(1);
		}
	}

	AddVertex(0, capHeight, 0);
	indices_v.push_back(sides + 1);
}

void PyramidMesh::AddVertex(float x, float y, float z)
{
	vertices_v.push_back(x);
	vertices_v.push_back(y);
	vertices_v.push_back(z);
}


