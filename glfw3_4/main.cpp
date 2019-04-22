#include <iostream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameEngine.h"
#include "ShadersCreator.h"


using namespace std;

glm::mat4 GetTransform() {

	// Create transformation matrix4 and edit pose rot and scale
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(3.0f, 1.0f, 0.0f));
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	return trans;
}

int main()
{

	GameEngine Engine(600, 500, "MyGameEngine", "shader.vert", "shader.frag");



	Engine.StartEngineLoop();


	return 0;
}


