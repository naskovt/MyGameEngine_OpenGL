#ifndef MESH_H
#define MESH_H
#include <vector>
#include <Math.h>
#include <vector>
#include "CoreStructures.h"

class Mesh {
public:
	float* vertices;
	float* normals;
	unsigned int* indices;

	unsigned int indicesSize;
	unsigned int verticesSize;

	Mesh() : vertices(nullptr), indices(nullptr), normals(nullptr), indicesSize(0), verticesSize(0) {};
	~Mesh()
	{
		delete vertices;
		delete indices;
	}

protected:

	void RotatePointUpAxis(Vector3& from, Vector3& rotatedResult, float angle)
	{
		// convert degrees to radians
		const float radians = angle * 3.14159265f / 180;

		float s = sin(radians);
		float c = cos(radians);

		rotatedResult.x = from.x * c - from.z * s;
		rotatedResult.z = from.x * s + from.z * c;
	}

	//void LoadDataToMeshArrays(std::vector<float>& vertices_v, std::vector<unsigned int>& indices_v, std::vector<float>& normals_v) {
	void LoadDataToMeshArrays(std::vector<float>& vertices_v, std::vector<unsigned int>& indices_v) {

		vertices = &vertices_v[0];
		indices = &indices_v[0];

		indicesSize = indices_v.size();
		verticesSize = vertices_v.size();

		//if (normals_v.count != )
		//{

		//}

	}
};
#endif
