#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "GameEngine.h"
#include "Enumerators.h"
#include "ShadersCreator.h"


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

int main()
{

	// TODO make better multiple shader loading
	GameEngine Engine(300, 300, "MyGameEngine");

	//TODO example solution: Engine.MaterialsManager.AddMaterial(make_pair("Red_Material", Material(shader, 1, 0, 0, 1)));
	// order is important! for now... need to init glfw3()... 
	CreateMaterials();


	Engine.AddObject("green triangle" , MeshType::Triangle, materials_map.find("Green_Material")->second);
	Engine.AddObject("red triangle", MeshType::Triangle, materials_map.find("Red_Material")->second);
	Engine.AddObject("blue square" , MeshType::Square, materials_map.find("Blue_Material")->second);

	Engine.GameObjects_Vector[0].Move(0.2f, 0.1f, 0.1f);

	Engine.GameObjects_Vector[1].Move(2, 2, 2);

	Engine.GameObjects_Vector[2].Scale(0.3f, 0.3f, 0.3f);

	Engine.GameObjects_Vector[2].Move(2,-2, 0);


	Engine.StartDrawingLoop();


	return 0;
}


