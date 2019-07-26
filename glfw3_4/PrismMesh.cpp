#include "PrismMesh.h"



PrismMesh::PrismMesh(int sides = 3, float height = 1, float radius = 1) {

	BuildMesh((sides < 3) ? 3 : sides, height, abs(radius));

	// assign vertices and indices
	Mesh::LoadDataToMeshArrays(vertices_v, indices_v);
}

void PrismMesh::BuildMesh(int sides, float height, float radius) {

	// build face
	Vector3 lastVertex;
	Vector3 currentVertex;
	const float sidesAngle = 360 / sides;

	for (int capsIndex = 0; capsIndex < 2; capsIndex++)
	{
		unsigned int CapCenterIndex = capsIndex * (sides + 1);

		const float capHeight = (capsIndex == 0) ? (height / 2) : -(height / 2);

		// first add a centered vertex of the face/cap 
		AddVertex(0, capHeight, 0);

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
				indices_v.push_back(CapCenterIndex);
				indices_v.push_back(CapCenterIndex + i);
				indices_v.push_back(CapCenterIndex + i + 1);
			}

			if (i + 1 == sides)
			{
				// the last triangle, connected to the first indices
				indices_v.push_back(CapCenterIndex);
				indices_v.push_back(CapCenterIndex + i + 1);
				indices_v.push_back(CapCenterIndex + 1);
			}
		}

		// add side triangles indices from top cap to bottom
		for (int i = 1; i <= sides; i++)
		{
			if (i < sides)
			{
				indices_v.push_back(i);
				indices_v.push_back(i + 1);
				indices_v.push_back(i + sides + 2);
			}
			else
			{
				indices_v.push_back(i);
				indices_v.push_back(1);
				indices_v.push_back(sides + 2);
			}
		}
		
		// add side triangles indices from bottom cap to top
		const int lastIndex = (sides * 2) + 1;
		for (int i = sides + 2; i <= lastIndex ; i++)
		{
			if (i < lastIndex)
			{
				indices_v.push_back(i);
				indices_v.push_back(i + 1);
				indices_v.push_back(i - sides - 1);
			}
			else
			{
				indices_v.push_back(i);		
				indices_v.push_back(sides + 2);
				indices_v.push_back(sides);
			}
		}
	}
}

void PrismMesh::AddVertex(float x, float y, float z)
{
	vertices_v.push_back(x);
	vertices_v.push_back(y);
	vertices_v.push_back(z);
}


