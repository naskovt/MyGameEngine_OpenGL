#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShadersCreator.h"
#include "BasicModel.h"
#include "Model_Assimp.h"
#include "Transform.h"

using namespace std;


class Object
{
public:
	Transform transform;

	Object() = delete;
	Object(const std::string name, MeshType meshType, Material& material);
	Object(const std::string name, const std::string& fileName, Material& material);
	
	~Object();

	void UpdateDrawing();

private:
	std::string _name;
	ModelInterface * _model;
};

#endif //OBJECT_H
