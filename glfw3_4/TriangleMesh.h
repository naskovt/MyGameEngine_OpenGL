#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "Mesh.h"

struct TriangleMesh : public Mesh {

	TriangleMesh() {

		vertices = new float[9]{
				 0.45f,  0.45f, 0.0f,  // top right
				 0.5f, -0.5f, 0.0f,  // bottom right
				-0.25f,  0.5f, 0.0f   // top left
		};

		indices = new unsigned int[3]{ 0,1,2 };

		this->verticesSize = 9;
		this->indicesSize = 3;
	};

	~TriangleMesh()
	{
		delete[] vertices;
		delete[] indices;
	}

};

#endif // !TRIANGLEMESH_H
