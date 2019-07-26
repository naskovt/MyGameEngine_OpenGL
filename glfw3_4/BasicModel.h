#ifndef BASICMODEL_H
#define BASICMODEL_H

#include "Mesh.h"
#include "Material.h"
#include "Enumerators.h"

#include "Shader.h"
#include "TriangleMesh.h"
#include "PrismMesh.h"
#include "SphereMesh.h"
#include "SquareMesh.h"
#include "PyramidMesh.h"
#include "ModelInterface.h"
#include "Definitions.h"

#include <glm/glm.hpp>
#include <glfw3.h>

class BasicModel : public ModelInterface
{
public:

	BasicModel(const MeshType meshType, const Material& mat);
	BasicModel(const MeshType meshType, const MeshPrimitiveInfo& info, const Material& mat);
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
