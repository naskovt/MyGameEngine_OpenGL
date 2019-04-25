#include "Object.h"



Object::Object(const std::string name, MeshType meshType, Material & material) :
	_name(name) , _model(meshType, material), _transform(){};


void Object::Move(float x, float y, float z) {

	this->_transform.transformMatrix = glm::translate(this->_transform.transformMatrix, glm::vec3(x, y, z));
}

void Object::RotateAround(float angle, float xAxis, float yAxis, float zAxis) {

	this->_transform.transformMatrix = glm::rotate(this->_transform.transformMatrix, 
											glm::radians(angle), glm::vec3(xAxis, yAxis, zAxis));
}

void Object::Scale(float x, float y, float z) {

	this->_transform.transformMatrix = glm::scale(this->_transform.transformMatrix, glm::vec3(x,y,z));
}

void Object::UpdateDrawing() {

	this->_model.material.GetShader().setMatrix4("transform", this->_transform.transformMatrix);

	this->_model.RenderModel();
}

Object::~Object()
{

}
