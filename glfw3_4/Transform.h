#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Transform
{
public:

	Transform();

	glm::mat4 GetMVPMatrix();

	//void SetTransformationMatrix(glm::mat4& transformation);
	//glm::mat4 & GetTransformationMatrix();

	void Translate(float x, float y, float z);
	void Rotate(float angle, float x, float y, float z);
	void Scale(float x, float y, float z);

	~Transform();

private:
	glm::mat4 _transformation_Matrix;
};

#endif
