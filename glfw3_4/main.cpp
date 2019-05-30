#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "Definitions.h"

#define STB_IMAGE_IMPLEMENTATION

// Game Engine headers
#include "MaterialsManager.h"
#include "GameEngine.h"
#include "Shader.h"
#include "Enumerators.h"
#include "Model_Assimp.h"


// Custom simulation headers
#include "CarEngine.h"


using namespace std;

void UpdateOnStart();
void UpdateEachFrame();


// Custom simulation variables
vector < map<string, Object>::iterator> DashboardParent;
GameEngine* Engine;
CarEngine* carEngine;

Transform* car_t;
Shader* rpm_shader;

float updateRateFix;
float light_color[] = { 0.8f, 0.8f ,0.8f };
//
void InitCar() {

	Shader* car_shader = &Engine->Materials->GetMaterial("Car_mat").GetShader();
	car_t = &Engine->GetObject_It("Car")->second.transform;

	car_shader->use();
	car_shader->isSeparateMVP = true;
	car_shader->setVec3("lightColor", light_color);
	car_shader->setVec3("lightPos", Engine->GetObject_It("Light")->second.transform.GetPosition());
	//car_shader->setMatrix4("viewPos", Engine->GetObject_It("Light")->second.transform.GetMVPMatrix().View);

	car_t->Scale(0.10);
	car_t->Translate(5, 0, 0);
	car_t->Rotate(30, 1, 0, 0);
}


void InitLightSource() {

	Transform* light_t = &Engine->GetObject_It("Light")->second.transform;
	Shader* light_shader = &Engine->Materials->GetMaterial("Light_mat").GetShader();

	light_t->Translate(-0.3, 1, 0);
	light_t->Scale(0.3f);
	light_shader->use();
	light_shader->setFloat("l_Color", 0.9f);
}

void Initialize() {

	// Engine main initialization
	Engine = new GameEngine(SCREEN_WIDTH, SCREEN_HEIGHT, "MyGameEngine");


	// LOAD RESOURCES
	Engine->Materials->LoadShaders(vector<string>{ "background_shader", "rpm_shader", "car_shader", "light_shader", "diffuse_shader" });

	Engine->Materials->LoadTextures("../Resources/textures",
		vector<string>{ "buffer_allocator.png", "dashboard_d.png", "box_d.jpg", "car_d.jpg", "rpm_d.png", "rpm_a.png"});

	// CREATE MATERIALS
	Engine->Materials->CreateMaterial("RPM_bar_mat", "rpm_shader", vector<string>{ "rpm_d.png", "rpm_a.png"});
	Engine->Materials->CreateMaterial("Background_mat", "background_shader", vector<string>{ "dashboard_d.png"});
	Engine->Materials->CreateMaterial("Box_mat", "diffuse_shader", vector<string>{ "box_d.jpg"});
	Engine->Materials->CreateMaterial("Car_mat", "car_shader", vector<string>{ "car_d.jpg"});
	Engine->Materials->CreateMaterial("Light_mat", "light_shader");


	UpdateOnStart();
}

void UpdateOnStart() {

	updateRateFix = 5;

	const string modelsFolder = "../Resources/models/";

	Engine->CreateObject("RPM_bar", modelsFolder+ "quad.obj", Engine->Materials->GetMaterial("RPM_bar_mat"));
	Engine->CreateObject("Background", modelsFolder + "quad.obj", Engine->Materials->GetMaterial("Background_mat"));
	Engine->CreateObject("Car", modelsFolder + "ford.obj", Engine->Materials->GetMaterial("Car_mat"));
	Engine->CreateObject("Light", modelsFolder + "box.obj", Engine->Materials->GetMaterial("Light_mat"));


	Engine->GetObject_It("Background")->second.transform.Scale(3);
	Engine->GetObject_It("RPM_bar")->second.transform.Scale(0.7);
	Engine->GetObject_It("RPM_bar")->second.transform.Translate(-0.3, 0, 0);

	rpm_shader = &Engine->Materials->GetMaterial("RPM_bar_mat").GetShader();

	InitLightSource();
	InitCar();

	carEngine = new CarEngine(900, 6800, 37 * updateRateFix, 30 * updateRateFix, 1500);
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

	car_t->Rotate(0.4 * updateRateFix,0,1,0);

	rpm_shader->setFloat("_gasValue", carEngine->GetNormalizedRPM());
}

int main()
{
	Initialize();

	Engine->StartGameLoop(UpdateEachFrame);

	return 0;
}


