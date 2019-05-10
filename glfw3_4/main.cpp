#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "GameEngine.h"
#include "Enumerators.h"
#include "ShadersCreator.h"
#include "Constants.h"


using namespace std;

ShadersCreator shader;
std::map< std::string, Material > materials_map;

GameEngine* Engine;

void UpdateOnStart();
void UpdateEachFrame();

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

	Engine->AddObject("green triangle" , MeshType::Triangle, materials_map.find("Green_Material")->second);
	Engine->AddObject("red triangle", MeshType::Triangle, materials_map.find("Red_Material")->second);
	Engine->AddObject("blue square", MeshType::Square, materials_map.find("Blue_Material")->second);

	Engine->GameObjects_Vector[0].transform.Translate(0.0f, 1.0f, -2.0f);

	Engine->GameObjects_Vector[1].transform.Translate(1.0f, 1.0f, -1.0f);

	Engine->GameObjects_Vector[2].transform.Scale(1.2f, 1.2f, 1.2f);

	Engine->GameObjects_Vector[2].transform.Rotate(45, 1, 0, 0);

}

void UpdateEachFrame() {

	if (Engine->isKeyPressed_W)
	{
		Engine->GameObjects_Vector[0].transform.Rotate(1, 1, 0, 0);
		Engine->GameObjects_Vector[2].transform.Rotate(2, 0, 1, 0);
	}
}

int main()
{
	Initialize();

	Engine->StartGameLoop(UpdateEachFrame);


	return 0;
}


