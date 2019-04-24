#include <iostream>
#include <sstream>
#include <string>
#include <vector>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameEngine.h"


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
	// TODO make better multiple shader loading
	GameEngine Engine(300, 300, "MyGameEngine", "shader.vert", "shader.frag");

	Engine.AddObject("tri1");
	Engine.AddObject("tri2");
	Engine.AddObject("tri3");

	Engine.GameObjects_Vector[0].Move(glm::vec3(0.5f, 0.2f, 0.1f));
	Engine.GameObjects_Vector[1].Move(glm::vec3(0.1f, 0.82f, 0.1f));
	Engine.GameObjects_Vector[2].Move(glm::vec3(0.15f, 0.52f, 0.9f));

	Engine.StartDrawingLoop();


	return 0;
}


