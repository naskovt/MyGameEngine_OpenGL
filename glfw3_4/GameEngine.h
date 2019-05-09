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

	GameEngine() = delete;

	//GameEngine(const unsigned int SCR_WIDTH_set, const unsigned int SCR_HEIGHT_set, const char* windowName,
	//
	//	std::map< std::string, Material >& materials_map_ptr, const char* vertShaderName, const char* fragShaderName);

	GameEngine(const unsigned int SCR_WIDTH_set, const unsigned int SCR_HEIGHT_set, const char* windowName);

	void StartDrawingLoop();

	bool Initialize();

	void AddObject(const std::string & name, MeshType meshType, Material & material);

	~GameEngine();

private:

	//void framebuffer_size_callback_(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);

	char* vertexShaderSource;
	char* fragmentShaderSource;

	//std::map< std::string, Material > & _materials_map_ptr;

	////Temporal transform for just 1 triangle object
	glm::mat4 trans;

	GLFWwindow* _window;
};

#endif // !GAMEENGINE_H
