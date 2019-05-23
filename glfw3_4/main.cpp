#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#define STB_IMAGE_IMPLEMENTATION

#include "GameEngine.h"
#include "ShadersCreator.h"
#include "Enumerators.h"
#include "Constants.h"
#include "Model_Assimp.h"

using namespace std;

ShadersCreator shader;
std::map< std::string, Material > materials_map;

GameEngine* Engine;

void UpdateOnStart();
void UpdateEachFrame();

map<string, Object>::iterator myObj_Ptr;

void CreateMaterials() {

	shader = ShadersCreator("shader.vert", "shader.frag");

	materials_map.insert(make_pair("Red_Material", Material(shader, 1, 0, 0, 1)));
	materials_map.insert(make_pair("Green_Material", Material(shader, 0, 1, 0, 1)));
	materials_map.insert(make_pair("Blue_Material", Material(shader, 0, 0, 1, 1)));
}


void Initialize() {

	// TODO make better multiple shader loading
	Engine = new GameEngine(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "MyGameEngine");

	//TODO create MaterialsManager -> example solution: Engine.MaterialsManager.AddMaterial(make_pair("Red_Material", Material(shader, 1, 0, 0, 1)));
	
	// order is important! for now... need to init glfw3()... 
	CreateMaterials();

	UpdateOnStart();
}

void UpdateOnStart() {

	Engine->CreateObject("box", "../Resources/box/box.obj", materials_map.find("Red_Material")->second);

	myObj_Ptr = Engine->GetObjectIT_ByName("box");
	myObj_Ptr->second.transform.Translate(0.0f, 0.0f, -1.0f);

	float scaleObj = 0.01f;
	myObj_Ptr->second.transform.Scale(scaleObj, scaleObj, scaleObj);

}


float rotationSpeed = 2.0f;

void UpdateEachFrame() {

	if (Engine->InputManager->isKeyPressed_W)
	{
		myObj_Ptr->second.transform.Rotate(rotationSpeed, 1, 0, 0);
	}

	if (Engine->InputManager->isKeyPressed_S)
	{
		myObj_Ptr->second.transform.Rotate(-rotationSpeed, 1, 0, 0);
	}

	if (Engine->InputManager->isKeyPressed_A)
	{
		myObj_Ptr->second.transform.Rotate(rotationSpeed, 0, 1, 0);
	}

	if (Engine->InputManager->isKeyPressed_D)
	{
		myObj_Ptr->second.transform.Rotate(-rotationSpeed, 0, 1, 0);
	}

}

int main()
{
	Initialize();

	Engine->StartGameLoop(UpdateEachFrame);

	return 0;
}


