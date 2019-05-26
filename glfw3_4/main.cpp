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
Shader* rpm_shader;
GameEngine* Engine;
CarEngine* carEngine;
//


void Initialize() {

	// Engine main initialization
	Engine = new GameEngine(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "MyGameEngine");


	// LOAD RESOURCES
	Engine->Materials->LoadShaders(vector<pair<string, string>>{ make_pair("background_shader.vert", "background_shader.frag"),
																make_pair( "rpm_shader.vert", "rpm_shader.frag") });
	Engine->Materials->LoadTextures("../Resources/textures", 
		vector<string>{ "buffer_allocator.png", "dashboard_d.png", "rpm_d.png", "rpm_a.png"});

	// CREATE MATERIALS
	Engine->Materials->CreateMaterial("RPM_bar_mat", "rpm_shader", vector<string>{ "rpm_d.png", "rpm_a.png"});
	Engine->Materials->CreateMaterial("Background_mat", "background_shader", vector<string>{ "dashboard_d.png"});


	UpdateOnStart();
}

void UpdateOnStart() {

	Engine->CreateObject("RPM_bar", "../Resources/models/quad.obj", Engine->Materials->GetMaterial("RPM_bar_mat"));
	Engine->CreateObject("Background", "../Resources/models/quad.obj", Engine->Materials->GetMaterial("Background_mat"));


	DashboardParent.push_back(Engine->GetObject_It("Background"));
	DashboardParent.push_back(Engine->GetObject_It("RPM_bar"));

	Engine->GetObject_It("Background")->second.transform.Scale(3);
	Engine->GetObject_It("RPM_bar")->second.transform.Scale(0.7);
	Engine->GetObject_It("RPM_bar")->second.transform.Translate(-0.3, 0, 0);

	rpm_shader = &Engine->Materials->GetMaterial("RPM_bar_mat").GetShader();

	carEngine = new CarEngine(900, 6800, 3.7,3,800);
}


float rotationSpeed = 0.1f;
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

	rpm_shader->setFloat("_gasValue", carEngine->GetNormalizedRPM());

	//cout << "RPM : " << carEngine->GetNormalizedRPM() << endl;;
}

int main()
{
	Initialize();

	Engine->StartGameLoop(UpdateEachFrame);

	return 0;
}


