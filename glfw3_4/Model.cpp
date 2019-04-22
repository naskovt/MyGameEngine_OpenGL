#include "Model.h"



Model::Model()
{
	_vertices = new float[9]{
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		//-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left
	};

	_indices = new unsigned int[9]{  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
}


Model::~Model()
{
	delete[] _vertices;
	delete[] _indices;
}
