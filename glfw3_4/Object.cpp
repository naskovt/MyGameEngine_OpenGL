#include "Object.h"
#include "Constants.h"


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

	// create MVP matrix here for testing

	//this->_transform.transformMatrix = glm::translate(this->_transform.transformMatrix, glm::vec3(0.0f, 0.0f, -0.1f));

	glm::mat4 model_Matrix		= glm::translate(this->_transform.transformMatrix, glm::vec3(0.0f, -2.0f, -100.1f));
	//glm::mat4 model_Matrix		= glm::mat4(1.0f);
	glm::mat4 view_Matrix		= glm::mat4(1.0f);
	glm::mat4 projection_Matrix = glm::mat4(1.0f);
	glm::mat4 mvp_Matrix		= glm::mat4(1.0f);

	model_Matrix = glm::rotate(model_Matrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// move the camera backwards (move all objects forward)
	view_Matrix			= glm::translate(view_Matrix, glm::vec3(0.10f, 0.0f, -1.0f));

	// apply perspective
	projection_Matrix	= glm::perspective(glm::radians(45.0f), (float)(Constants::SCREEN_WIDTH / Constants::SCREEN_HEIGHT), 0.1f, 100.0f);
	
	// MULTIPLY all transformations to create 3d view on a 2d plane
	//mvp_Matrix			= model_Matrix * view_Matrix;
	mvp_Matrix				= model_Matrix * view_Matrix * projection_Matrix;


	glm::vec4 test_vertex = glm::vec4(0.1, 0.1, 0.1, 1.0);
	test_vertex = test_vertex * view_Matrix;
	std::cout << "points After mvp: " << test_vertex.x << " | " << test_vertex.y << " | " << test_vertex.z;

	this->_model.material.GetShader().setMatrix4("mvpMatrix", mvp_Matrix);

	this->_model.RenderModel();
}

Object::~Object()
{

}
