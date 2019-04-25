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
	Object() = delete;
	Object(const std::string name, MeshType meshType, Material& material);
	~Object();

	void Move(float xAxis, float yAxis, float zAxis);

	void RotateAround(float angle, float xAxis, float yAxis, float zAxis);

	void Scale(float x, float y, float z);

	void UpdateDrawing();

private:
	std::string _name;
	Model _model;
	Transform _transform;
};

#endif
