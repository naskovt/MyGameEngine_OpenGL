#pragma once
#include "Mesh.h"

struct TriangleMesh : public Mesh {



	TriangleMesh() {


			vertices = new float[9]{
				 0.5f,  0.5f, 0.0f,  // top right
				 0.5f, -0.5f, 0.0f,  // bottom right
				-0.5f,  0.5f, 0.0f   // top left
			};

			indices = new unsigned int[3]{  // note that we start from 0!
				0, 1, 2,  // first Triangle
			};
	};



};