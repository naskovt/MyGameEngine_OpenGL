#include "Object.h"


Object::Object(const std::string name, MeshType meshType, Material& material) :
	_name(name), _model(meshType, material), transform() {};

Object::Object(const std::string name, const std::string& fileName, Material& material) :
		_name(name), _model(fileName, material), transform() {};

void Object::UpdateDrawing() {

	this->_model.material.GetShader().setMatrix4("mvpMatrix", this->transform.GetMVPMatrix());

	this->_model.RenderModel();
}

void Object::PrintMeshInfo() 
{

	size_t vertSize = this->_model.GetMesh()->verticesSize /4;

	cout << "\n";
	cout << "Vertices num: " << vertSize;
	cout << "\n";

	for (size_t i = 0; i < vertSize; i++)
	{
		cout << "V_" << i << " : " << this->_model.GetMesh()->vertices[i];
		cout << "\n";
	}

}

Object::~Object()
{

}
