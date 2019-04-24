#include "Object.h"



Object::Object(std::string name) : _name(name) , _model(Mesh()), _transform(){};


void Object::Move(glm::vec3 position) {

	this->_transform.transformMatrix = glm::translate(this->_transform.transformMatrix, position);
}

void Object::RotateAround(float angle, glm::vec3 axis) {

	this->_transform.transformMatrix = glm::rotate(this->_transform.transformMatrix, glm::radians(angle), axis);
}

void Object::Scale(float x, float y, float z) {

	this->_transform.transformMatrix = glm::scale(this->_transform.transformMatrix, glm::vec3(x,y,z));
}

void Object::UpdateDrawing(ShadersCreator shader) {

	shader.setMatrix4("transform", this->_transform.transformMatrix);

	this->_model.RenderModel(shader);
}

Object::~Object()
{

}
