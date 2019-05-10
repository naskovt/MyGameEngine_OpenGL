#include "Object.h"


Object::Object(const std::string name, MeshType meshType, Material & material) :
	_name(name) , _model(meshType, material), transform(){};

void Object::UpdateDrawing() {

	this->_model.material.GetShader().setMatrix4("mvpMatrix", this->transform.GetMVPMatrix());

	this->_model.RenderModel();
}

Object::~Object()
{

}
