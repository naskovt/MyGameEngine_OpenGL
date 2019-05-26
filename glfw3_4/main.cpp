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
Object* turntable;
float updateRateFix;
//


void Initialize() {

	// Engine main initialization
	Engine = new GameEngine(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "MyGameEngine");


	// LOAD RESOURCES
	Engine->Materials->LoadShaders(vector<pair<string, string>>{ make_pair("background_shader.vert", "background_shader.frag"),
																make_pair( "rpm_shader.vert", "rpm_shader.frag"),
																make_pair("diffuse_shader.vert", "diffuse_shader.frag")});
	Engine->Materials->LoadTextures("../Resources/textures", 
		vector<string>{ "buffer_allocator.png", "dashboard_d.png", "box_d.jpg", "rpm_d.png", "rpm_a.png"});

	// CREATE MATERIALS
	Engine->Materials->CreateMaterial("RPM_bar_mat", "rpm_shader", vector<string>{ "rpm_d.png", "rpm_a.png"});
	Engine->Materials->CreateMaterial("Background_mat", "background_shader", vector<string>{ "dashboard_d.png"});
	Engine->Materials->CreateMaterial("Box_mat", "diffuse_shader", vector<string>{ "box_d.jpg"});


	UpdateOnStart();
}

void UpdateOnStart() {

	updateRateFix = 0.1;

	Engine->CreateObject("RPM_bar", "../Resources/models/quad.obj", Engine->Materials->GetMaterial("RPM_bar_mat"));
	Engine->CreateObject("Background", "../Resources/models/quad.obj", Engine->Materials->GetMaterial("Background_mat"));
	Engine->CreateObject("Car", "../Resources/models/box.obj", Engine->Materials->GetMaterial("Box_mat"));


	DashboardParent.push_back(Engine->GetObject_It("Car"));

	turntable = &Engine->GetObject_It("Car")->second;

	turntable->transform.Scale(0.2);
	turntable->transform.Translate(4, 0, 0);
	turntable->transform.Rotate(30, 1, 0, 0);

	Engine->GetObject_It("Background")->second.transform.Scale(3);
	Engine->GetObject_It("RPM_bar")->second.transform.Scale(0.7);
	Engine->GetObject_It("RPM_bar")->second.transform.Translate(-0.3, 0, 0);

	rpm_shader = &Engine->Materials->GetMaterial("RPM_bar_mat").GetShader();

	carEngine = new CarEngine(900, 6800, 37 * updateRateFix, 30 * updateRateFix,1500);
}


float rotationSpeed = 0.1f;
float gasValue = 0.0f;

void UpdateEachFrame() {

	//for (map<string, Object>::iterator objectIt : DashboardParent)
	//{

	//	if (Engine->InputManager->isKeyPressed_W)
	//	{
	//		objectIt->second.transform.Rotate(rotationSpeed, 1, 0, 0);
	//	}

	//	if (Engine->InputManager->isKeyPressed_A)
	//	{
	//		objectIt->second.transform.Rotate(rotationSpeed, 0, 1, 0);
	//	}

	//	if (Engine->InputManager->isKeyPressed_S)
	//	{
	//		objectIt->second.transform.Rotate(-rotationSpeed, 1, 0, 0);
	//	}

	//	if (Engine->InputManager->isKeyPressed_D)
	//	{
	//		objectIt->second.transform.Rotate(-rotationSpeed, 0, 1, 0);
	//	}
	//}


	if (Engine->InputManager->isKeyPressed_E)
	{
		carEngine->Throttle();
	}
	else
	{
		carEngine->Idle();
	}

	turntable->transform.Rotate(1* updateRateFix,0,1,0);

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


