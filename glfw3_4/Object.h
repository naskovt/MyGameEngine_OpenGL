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
	Object(std::string name);
	~Object();

	void Move(glm::vec3 position);

	void RotateAround(float angle, glm::vec3 axis);

	void Scale(float x, float y, float z);

	void UpdateDrawing(ShadersCreator shader);

private:
	std::string _name;
	Model _model;
	Transform _transform;
};

#endif
