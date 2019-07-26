#ifndef SQUARE_H
#define SQUARE_H

#include "Mesh.h"

struct SquareMesh : public Mesh {

	SquareMesh() {


		vertices = new float[12]{
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};

		indices = new unsigned int[6]{
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		this->verticesSize = 12;
		this->indicesSize = 6;

	};



};

#endif // !SQUARE_H