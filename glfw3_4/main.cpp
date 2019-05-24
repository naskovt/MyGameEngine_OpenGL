#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

// Game Engine headers
#define STB_IMAGE_IMPLEMENTATION
#include "MaterialsManager.h"
#include "GameEngine.h"
#include "Shader.h"
#include "Enumerators.h"
#include "Constants.h"
#include "Model_Assimp.h"


// Custom simulation headers
#include "CarEngine.h"


using namespace std;

void UpdateOnStart();
void UpdateEachFrame();


// Custom simulation variables
vector < map<string, Object>::iterator> DashboardParent;
Material* rpm_material;
GameEngine* Engine;
CarEngine* carEngine;
//


void Initialize() {

	// TODO make better multiple shader loading
	Engine = new GameEngine(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "MyGameEngine");

	Engine->Materials->CreateMaterial("Leather_mat", new Shader("diffuse_shader.vert", "diffuse_shader.frag"));
	Engine->Materials->CreateMaterial("Metal_mat", new Shader("metal_shader.vert", "metal_shader.frag"));
	Engine->Materials->CreateMaterial("RPM_mat", new Shader("rpm_shader.vert", "rpm_shader.frag"));

	UpdateOnStart();
}

void UpdateOnStart() {

	Engine->CreateObject("Dashboard", "../Resources/dashboard/dashboard.obj", Engine->Materials->GetMaterial("Leather_mat"));
	Engine->CreateObject("Gauges", "../Resources/dashboard/gauges.obj", Engine->Materials->GetMaterial("Metal_mat"));
	Engine->CreateObject("RPM", "../Resources/dashboard/RPM.obj", Engine->Materials->GetMaterial("RPM_mat"));
	Engine->CreateObject("KPH", "../Resources/dashboard/KPH.obj", Engine->Materials->GetMaterial("RPM_mat"));

	DashboardParent.push_back(Engine->GetObject_It("Dashboard"));
	DashboardParent.push_back(Engine->GetObject_It("Gauges"));
	DashboardParent.push_back(Engine->GetObject_It("RPM"));
	DashboardParent.push_back(Engine->GetObject_It("KPH"));

	float scaleObj = 1;

	for (map<string, Object>::iterator objectIt : DashboardParent)
	{
		objectIt->second.transform.Translate(0.0f, 0.0f, -5.0f);
		objectIt->second.transform.Scale(scaleObj, scaleObj, scaleObj);
	}

	rpm_material = &Engine->Materials->GetMaterial("RPM_mat");
	carEngine = new CarEngine(900, 6800, 250, 200, 300);
}


float rotationSpeed = 2.0f;
float gasValue = 0.0f;

void UpdateEachFrame() {

	for (map<string, Object>::iterator objectIt : DashboardParent)
	{

		if (Engine->InputManager->isKeyPressed_W)
		{
			objectIt->second.transform.Rotate(rotationSpeed, 1, 0, 0);
		}

		if (Engine->InputManager->isKeyPressed_A)
		{
			objectIt->second.transform.Rotate(rotationSpeed, 0, 1, 0);
		}

		if (Engine->InputManager->isKeyPressed_S)
		{
			objectIt->second.transform.Rotate(-rotationSpeed, 1, 0, 0);
		}

		if (Engine->InputManager->isKeyPressed_D)
		{
			objectIt->second.transform.Rotate(-rotationSpeed, 0, 1, 0);
		}
	}



	if (Engine->InputManager->isKeyPressed_E)
	{
		carEngine->Throttle();
	}
	else
	{
		carEngine->Idle();
	}


	// TODO Update gas in RPM gauges material
	rpm_material->GetShader().setFloat("_gasValue", carEngine->GetNormalizedRPM());

}

int main()
{
	Initialize();

	Engine->StartGameLoop(UpdateEachFrame);

	return 0;
}


