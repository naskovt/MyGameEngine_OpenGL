#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

#include "CoreStructures.h"

class Transform
{
public:

	Transform();
	~Transform();
	PVM_Matrix GetMVPMatrix();
	Vector3 GetPosition() const;
	//std::vector<float> GetPosition_Array() const;
	

	void Translate(float x, float y, float z);
	void Rotate(float angle, float x, float y, float z);
	void Scale(float x, float y, float z);
	void Scale(float scale);


private:
	glm::mat4 _transformation_Matrix;
	Vector3 position;
};

#endif
