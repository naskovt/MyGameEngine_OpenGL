#include "Object.h"


Object::Object() :  transform()
{
};

Object::Object( MeshType meshType, Material& material) : transform() {

	BasicModel* basicModel = new BasicModel(meshType, material);
	_model = dynamic_cast<ModelInterface*> (basicModel);

};

Object::Object( const std::string& fileName, Material& material) : transform() {

	ModelAssimp* assimpModel = new ModelAssimp(fileName, material);
	_model = dynamic_cast<ModelInterface*> (assimpModel);
};


void Object::UpdateDrawing() {

	if (this->_model != nullptr)
	{
		this->_model->material.GetShader().setMatrix4("mvpMatrix", this->transform.GetMVPMatrix());

		this->_model->RenderModel();
	}

}


Object::~Object()
{
	//delete _model;
}
