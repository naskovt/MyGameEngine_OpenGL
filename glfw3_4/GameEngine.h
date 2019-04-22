#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <glfw3.h>
#include "ShadersCreator.h"
#include "Object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameEngine
{
public:

	GameEngine() = delete;

	GameEngine(const unsigned int SCR_WIDTH_set, const unsigned int SCR_HEIGHT_set,
		const char* windowName, const char* vertShaderName, const char* fragShaderName);

	void StartEngineLoop();

	bool Initialize();

	void AddObject(std::string name);

	~GameEngine();

private:

	//void framebuffer_size_callback_(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);

	const char* vertexShaderSource;
	const char* fragmentShaderSource;

	ShadersCreator _customShaders;

	unsigned int VBO, VAO, EBO;

	////Temporal transform for just 1 triangle object
	glm::mat4 trans;
	GLFWwindow* _window;
	std::vector<Object> _objectsVector;
};

#endif // !GAMEENGINE_H
