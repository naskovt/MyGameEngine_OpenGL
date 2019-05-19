#include "Object.h"


Object::Object(const std::string name, MeshType meshType, Material& material) :
	_name(name), transform() {

	BasicModel* basicModel = new BasicModel(meshType, material);
	_model = dynamic_cast<ModelInterface*> (basicModel);

};

Object::Object(const std::string name, const std::string& fileName, Material& material) :
		_name(name), transform() {

	ModelAssimp* assimpModel = new ModelAssimp(fileName, material);
	_model = dynamic_cast<ModelInterface*> (assimpModel);
};


void Object::UpdateDrawing() {

	this->_model->material.GetShader().setMatrix4("mvpMatrix", this->transform.GetMVPMatrix());

	this->_model->RenderModel();
}


Object::~Object()
{
	//delete _model;
}
