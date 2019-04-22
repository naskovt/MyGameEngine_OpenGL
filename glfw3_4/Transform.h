#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>


class Transform
{
public:
	Transform();
	~Transform();
private:
	glm::mat4 _transformMatrix;
};

#endif
