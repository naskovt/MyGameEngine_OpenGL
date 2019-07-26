#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "BasicModel.h"
#include "Model_Assimp.h"
#include "Transform.h"
#include "CoreStructures.h"

using namespace std;


class Object
{
public:
	Transform transform;

	Object();
	Object( const MeshType meshType, const Material& material);
	Object( const MeshType meshType, const MeshPrimitiveInfo& info, const Material& material);
	Object( const std::string& fileName, const Material& material);
	
	~Object();

	void UpdateDrawing();

private:
	ModelInterface * _model;
	string _mvpName;
};

#endif //OBJECT_H
