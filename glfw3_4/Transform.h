#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>


class Transform
{
public:
	glm::mat4 transformMatrix;

	Transform();

	~Transform();
private:
};

#endif
