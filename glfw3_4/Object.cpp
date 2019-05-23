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
		if (this->_model->material._color[0] == 1)
		{
			// if we are with a red material (rpm gauges animation)

			// set timed color transition
			float timeValue = glfwGetTime();
			float timed_Value = (sin(timeValue) / 2.0f) + 0.5f;

			this->_model->material.GetShader().setFloat("timer", timed_Value);
		}



		this->_model->material.GetShader().setMatrix4("mvpMatrix", this->transform.GetMVPMatrix());

		this->_model->RenderModel();
	}

}


Object::~Object()
{
	//delete _model;
}
