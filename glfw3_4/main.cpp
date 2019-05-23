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

ShadersCreator dashboard_shader;
ShadersCreator metal_shader;
ShadersCreator rpm_shader;

std::map< std::string, Material > materials_map;

GameEngine* Engine;

void UpdateOnStart();
void UpdateEachFrame();

map<string, Object>::iterator myObj_Ptr;

vector < map<string, Object>::iterator> DashboardParent;

void CreateMaterials() {

	dashboard_shader = ShadersCreator("diffuse_shader.vert", "diffuse_shader.frag");
	metal_shader = ShadersCreator("metal_shader.vert", "metal_shader.frag");
	rpm_shader = ShadersCreator("rpm_shader.vert", "rpm_shader.frag");

	materials_map.insert(make_pair("Leather_mat", Material(dashboard_shader, 0, 0, 0, 1)));
	materials_map.insert(make_pair("Metal_mat", Material(metal_shader, 0, 0, 0, 1)));
	materials_map.insert(make_pair("RPM_mat", Material(rpm_shader, 1, 0, 0, 1)));
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

	Engine->CreateObject("Dashboard", "../Resources/dashboard/dashboard.obj", materials_map.find("Leather_mat")->second);
	Engine->CreateObject("Gauges", "../Resources/dashboard/gauges.obj", materials_map.find("Metal_mat")->second);
	Engine->CreateObject("RPM", "../Resources/dashboard/RPM.obj", materials_map.find("RPM_mat")->second);
	Engine->CreateObject("KPH", "../Resources/dashboard/KPH.obj", materials_map.find("RPM_mat")->second);

	DashboardParent.push_back(Engine->GetObjectIT_ByName("Dashboard"));
	DashboardParent.push_back(Engine->GetObjectIT_ByName("Gauges"));
	DashboardParent.push_back(Engine->GetObjectIT_ByName("RPM"));
	DashboardParent.push_back(Engine->GetObjectIT_ByName("KPH"));

	float scaleObj = 1;

	for (map<string, Object>::iterator objectIt : DashboardParent)
	{
		objectIt->second.transform.Translate(0.0f, 0.0f, -5.0f);
		objectIt->second.transform.Scale(scaleObj, scaleObj, scaleObj);
	}

}


float rotationSpeed = 2.0f;

void UpdateEachFrame() {

	for (map<string, Object>::iterator objectIt : DashboardParent)
	{

		if (Engine->InputManager->isKeyPressed_W)
		{
			objectIt->second.transform.Rotate(rotationSpeed, 1, 0, 0);
		}

		if (Engine->InputManager->isKeyPressed_S)
		{
			objectIt->second.transform.Rotate(-rotationSpeed, 1, 0, 0);
		}

		if (Engine->InputManager->isKeyPressed_A)
		{
			objectIt->second.transform.Rotate(rotationSpeed, 0, 1, 0);
		}

		if (Engine->InputManager->isKeyPressed_D)
		{
			objectIt->second.transform.Rotate(-rotationSpeed, 0, 1, 0);
		}
	}

}

int main()
{
	Initialize();

	Engine->StartGameLoop(UpdateEachFrame);

	return 0;
}


