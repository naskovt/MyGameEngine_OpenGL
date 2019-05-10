#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
//#include <thread>

#include "GameEngine.h"
#include "Enumerators.h"
#include "ShadersCreator.h"
#include "Constants.h"

typedef std::chrono::high_resolution_clock Clock;

using namespace std;

//std::map< std::string, ShadersCreator > shaders_map;
ShadersCreator shader;
std::map< std::string, Material > materials_map;



void CreateMaterials() {

	shader = ShadersCreator("shader.vert", "shader.frag");

	materials_map.insert(make_pair("Red_Material", Material(shader, 1, 0, 0, 1)));
	materials_map.insert(make_pair("Green_Material", Material(shader, 0, 1, 0, 1)));
	materials_map.insert(make_pair("Blue_Material", Material(shader, 0, 0, 1, 1)));
}

//void UpdateGameMethod() {
//	// 60 times called per second
//
//	sleep(16.6f);
//}

int main()
{


	// TODO make better multiple shader loading
	GameEngine Engine(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "MyGameEngine");

	//TODO create MaterialsManager -> example solution: Engine.MaterialsManager.AddMaterial(make_pair("Red_Material", Material(shader, 1, 0, 0, 1)));
	
	// order is important! for now... need to init glfw3()... 
	CreateMaterials();

	//Engine.AddObject("green triangle" , MeshType::Triangle, materials_map.find("Green_Material")->second);
	//Engine.AddObject("red triangle", MeshType::Triangle, materials_map.find("Red_Material")->second);

	Engine.AddObject("blue square" , MeshType::Square, materials_map.find("Blue_Material")->second);

	Engine.GameObjects_Vector[0].transform.Translate(0.0f, 1.0f, -2.0f);

	Engine.GameObjects_Vector[0].transform.Scale(1.2f, 1.2f, 1.2f);

	Engine.GameObjects_Vector[0].transform.Rotate(45, 1, 0, 0);

	//auto t1 = Clock::now();
	//auto t2 = Clock::now();
	//std::cout << "Delta t2-t1: "
	//	<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
	//	<< " milliseconds" << std::endl;

	//thread threadUpdateGame(UpdateGameMethod, "UpdateGame");

	Engine.StartDrawingLoop();


	return 0;
}


