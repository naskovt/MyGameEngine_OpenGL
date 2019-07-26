#include "Object.h"


Object::Object() :  transform()
{
};

Object::Object( const MeshType meshType, const Material& material) : transform() {

	BasicModel* basicModel = new BasicModel(meshType, material);
	_model = dynamic_cast<ModelInterface*> (basicModel);
};

Object::Object( const MeshType meshType, const MeshPrimitiveInfo& info, const Material& material) : transform() {

	BasicModel* basicModel = new BasicModel(meshType, info, material);
	_model = dynamic_cast<ModelInterface*> (basicModel);
};

Object::Object( const std::string& fileName, const Material& material) : transform(){

	ModelAssimp* assimpModel = new ModelAssimp(fileName, material);
	_model = dynamic_cast<ModelInterface*> (assimpModel);
};


void Object::UpdateDrawing() {

	if (this->_model != nullptr)
	{
		this->_model->material.GetShader().use();

		//if (this->_model->material._color[0] == 1)
		//{
		//	// if we are with a red material (rpm gauges animation)

		//	// set timed color transition
		//	float timeValue = glfwGetTime();
		//	float timed_Value = (sin(timeValue) / 2.0f) + 0.5f;

		//	this->_model->material.GetShader().setFloat("timer", timed_Value);
		//}

		if (this->_model->material.GetShader().isSeparateMVP)
		{
			this->_model->material.GetShader().setMatrix4("model", this->transform.GetMVPMatrix().Model);
			this->_model->material.GetShader().setMatrix4("view", this->transform.GetMVPMatrix().View);
			this->_model->material.GetShader().setMatrix4("projection", this->transform.GetMVPMatrix().Projection);
		}
		else
		{
			// we multiply the matrices in reversed order, important!
			this->_model->material.GetShader().setMatrix4("mvp",this->transform.GetMVPMatrix().Projection
																	* this->transform.GetMVPMatrix().View
																	* this->transform.GetMVPMatrix().Model);
		}
		
		this->_model->RenderModel();
	}

}


Object::~Object()
{
	//delete _model;
}
