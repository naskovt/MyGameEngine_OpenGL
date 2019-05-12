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
#include "Input.h"

class GameEngine
{
public:

	Input* InputManager;


	GameEngine() = delete;
	GameEngine(const unsigned int SCR_WIDTH_set, const unsigned int SCR_HEIGHT_set, const char* windowName);

	~GameEngine();

	bool Initialize();
	void StartGameLoop(void (*UpdateGame)());
	Object& GetObjectByName(std::string name);
	void CreateObject(const std::string& name, MeshType meshType, Material& material);
	void CreateObject(const std::string& name, const std::string& fileName, Material & material);
	
private:

	char* vertexShaderSource;
	char* fragmentShaderSource;
	GLFWwindow* _window;
	std::map< std::string, Object > GameObjects_Map;

	void DrawGame();
};

#endif // !GAMEENGINE_H
