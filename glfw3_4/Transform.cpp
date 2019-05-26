#include "Transform.h"
#include "Constants.h"



Transform::Transform() : _transformation_Matrix(glm::mat4(1.0f))
{
};


Transform::~Transform()
{
}

void Transform::Translate(float x, float y, float z)
{
	_transformation_Matrix = glm::translate(_transformation_Matrix, glm::vec3(x, y, z));
}

void Transform::Rotate(float angle, float xAxis, float yAxis, float zAxis)
{
	_transformation_Matrix = glm::rotate(_transformation_Matrix,
		glm::radians(angle), glm::vec3(xAxis, yAxis, zAxis));
}

void Transform::Scale(float x, float y, float z)
{
	_transformation_Matrix = glm::scale(_transformation_Matrix, glm::vec3(x, y, z));
}

void Transform::Scale(float scale)
{
	_transformation_Matrix = glm::scale(_transformation_Matrix, glm::vec3(scale, scale, scale));
}

glm::mat4 Transform::GetMVPMatrix()
{
	glm::mat4 view_Matrix = glm::mat4(1.0f);
	glm::mat4 projection_Matrix = glm::mat4(1.0f);

	// TODO CAMERA is here for now - moving the camera backwards (move all objects forward)
	view_Matrix = glm::translate(view_Matrix, glm::vec3(0.0f, 0.0f, -3.0f));

	// TODO - should be with camera object - applying perspective
	projection_Matrix = glm::perspective(glm::radians(45.0f), (float)(Constants::SCREEN_WIDTH / Constants::SCREEN_HEIGHT), 0.1f, 100.0f);

	// MULTIPLY all transformations to create 3d view in the 2d window
	return projection_Matrix * view_Matrix * _transformation_Matrix;
}
