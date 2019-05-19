#ifndef BASICMODEL_H
#define BASICMODEL_H

#include "Mesh.h"
#include "Material.h"
#include "Enumerators.h"

#include "ShadersCreator.h"
#include "TriangleMesh.h"
#include "SquareMesh.h"
#include "ModelInterface.h"

#include <glm/glm.hpp>
#include <glfw3.h>

class BasicModel : public ModelInterface
{
public:

	BasicModel(MeshType meshType, Material& mat);
	//BasicModel(std::string fileName, Material & material);
	~BasicModel();

	Mesh* GetMesh() {
		return this->_mesh;
	}

	void RenderModel() override;

private:
	
	void LoadMeshToGPU();

	unsigned int VAO, VBO, EBO;

	Mesh* _mesh;
};

#endif
