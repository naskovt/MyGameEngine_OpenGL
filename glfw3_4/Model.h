#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "Material.h"
#include "Enumerators.h"

#include "ShadersCreator.h"
#include "TriangleMesh.h"
#include "SquareMesh.h"

#include <glm/glm.hpp>
#include <glfw3.h>

class Model
{
public:
	Model(MeshType meshType, Material& material);
	Model(std::string fileName, Material & material);
	~Model();

	Mesh* GetMesh() {
		return this->_mesh;
	}

	virtual void RenderModel();

	Material & material;
private:
	
	void LoadMeshToGPU();

	unsigned int VAO, VBO, EBO;

	Mesh* _mesh;
};

#endif
