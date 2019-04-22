#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>

#include "Model.h"
#include "Transform.h"

class Object
{
public:
	Object() = delete;
	Object(std::string name);
	~Object();

	void UpdateDrawing();

private:
	std::string _name;
	Model _model;
	Transform _transform;
};

#endif
