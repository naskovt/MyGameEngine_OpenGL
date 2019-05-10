#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShadersCreator.h"
#include "Model.h"
#include "Transform.h"

class Object
{
public:
	Transform transform;

	Object() = delete;
	Object(const std::string name, MeshType meshType, Material& material);
	~Object();

	void UpdateDrawing();

private:
	std::string _name;
	Model _model;
};

#endif
