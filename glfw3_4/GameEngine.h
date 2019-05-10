#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

#include <glad/glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShadersCreator.h"
#include "Material.h"
#include "TriangleMesh.h"
#include "Camera.h"
#include "Object.h"



class GameEngine
{
public:

	std::vector<Object> GameObjects_Vector;
	bool isKeyPressed_W;

	GameEngine() = delete;

	GameEngine(const unsigned int SCR_WIDTH_set, const unsigned int SCR_HEIGHT_set, const char* windowName);


	bool Initialize();

	void StartGameLoop(void (*UpdateGame)());


	void AddObject(const std::string & name, MeshType meshType, Material & material);

	~GameEngine();

private:

	char* vertexShaderSource;
	char* fragmentShaderSource;
	GLFWwindow* _window;

	void ProcessInput(GLFWwindow* window);
	void DrawGame();
};

#endif // !GAMEENGINE_H
