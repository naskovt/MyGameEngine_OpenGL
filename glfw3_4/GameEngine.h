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

#include "MaterialsManager.h"
#include "Shader.h"
#include "Material.h"
#include "TriangleMesh.h"
#include "Camera.h"
#include "Object.h"
#include "Input.h"

#include "TextRenderer.h"


class GameEngine
{
public:

	Input* InputManager;

	MaterialsManager* Materials;

	GameEngine() = delete;
	GameEngine(const unsigned int SCR_WIDTH_set, const unsigned int SCR_HEIGHT_set, const char* windowName, bool wireframeRendering);

	~GameEngine();

	bool Initialize();
	void StartGameLoop(void (*UpdateGame)(), void (*LateUpdateEachFrame)());
	map<string, Object>::iterator GetObject_It(std::string name);
	void CreateObject(const std::string& name, const MeshType meshType, const Material& material);
	void CreateObject(const std::string& name, const MeshType meshType, const MeshPrimitiveInfo& info, const Material& material);
	void CreateObject(const std::string& name, const std::string& fileName, const Material& material); 
	
	TextRenderer* m_test_obj;
private:

	char* vertexShaderSource;
	char* fragmentShaderSource;
	GLFWwindow* _window;
	std::map< std::string, Object > GameObjects_Map;
	bool m_WireframeRendering = false;


	void DrawGameObjects();
};

#endif // !GAMEENGINE_H
