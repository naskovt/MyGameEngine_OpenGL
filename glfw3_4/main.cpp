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
#include "TextRenderer.h"

// Custom simulation headers
#include "CarEngine.h"
#include "Object.h"

using namespace std;

void UpdateOnStart();
void UpdateEachFrame();

// Custom simulation variables
vector < map<string, Object>::iterator> objectsParent;
GameEngine* Engine;

Transform* sphere_t;
Transform* box_t;
Shader* phong_shader;
TextRenderer* txtRenderer;

const float updateRateFix = 5;

Transform* light_t;
float light_color[] = { 0.8f, 0.2f ,0.2f };
float ambientIntensity = 0.3f;
//

float rotationSpeed = 1.5f;
float movementSpeed = 0.2f;

void UpdateLightedObjectsShader() {

	phong_shader->use();
	Vector3 pose = Engine->GetObject_It("Light")->second.transform.GetPosition();
	phong_shader->setVec3("lightPos", pose);
}

void SetLightedObject(std::string objName) {


	static float spawOffset_X = -1.5f;

	box_t = &Engine->GetObject_It(objName)->second.transform;
	box_t->Scale(0.5f);
	box_t->Translate(spawOffset_X, 0, -3);
	spawOffset_X += 1.5f;
	box_t->Rotate(45, 1, 0, 0);

	UpdateLightedObjectsShader();

	objectsParent.push_back(Engine->GetObject_It(objName));

}

void InitLightSource() {

	Shader* light_shader = &Engine->Materials->GetMaterial("Light_mat").GetShader();
	light_shader->use();

	light_shader->setFloat("l_Color", 0.9f);

	light_t = &Engine->GetObject_It("Light")->second.transform;
	light_t->Translate(2, 1, -1);
	light_t->Scale(0.8f);

	phong_shader = &Engine->Materials->GetMaterial("Box_mat").GetShader();
	phong_shader->use();
	phong_shader->isSeparateMVP = true;
	phong_shader->setVec3("lightColor", light_color);
	phong_shader->setFloat("ambientIntensity", ambientIntensity);
	//phong_shader->setMatrix4("viewPos", Engine->GetObject_It("Light")->second.transform.GetMVPMatrix().View);
}

void Initialize() {

	const bool wireframeMode = true;

	Engine = new GameEngine(SCREEN_WIDTH, SCREEN_HEIGHT, "MyGameEngine", wireframeMode);

	// LOAD RESOURCES
	Engine->Materials->LoadShaders(vector<string>{"phong_shader", "light_shader", "text_shader"});
	Engine->Materials->LoadTextures("../Resources/textures", vector<string>{"box_d.jpg"});

	// CREATE MATERIALS
	Engine->Materials->CreateMaterial("Box_mat", "phong_shader", vector<string>{ "box_d.jpg"});
	Engine->Materials->CreateMaterial("Text_mat", "text_shader");
	Engine->Materials->CreateMaterial("Light_mat", "light_shader");

	txtRenderer = new TextRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, Engine->Materials->GetMaterial("Text_mat").GetShader());
	//txtRenderer->Load("../Resources/fonts/OCRAEXT.TTF", 24); 
	txtRenderer->Load("../Resources/fonts/Butcherman-Regular.ttf", 30);

}

void UpdateOnStart() {

	const string modelsFolder = "../Resources/models/";

	Engine->CreateObject("Light", MeshType::Sphere, MeshPrimitiveInfo(0.20f, 9, false), Engine->Materials->GetMaterial("Light_mat"));
	InitLightSource();

	Engine->CreateObject("Prism", MeshType::Prism, MeshPrimitiveInfo(0.50f, 10, 2.5f), Engine->Materials->GetMaterial("Box_mat"));
	Engine->CreateObject("Pyramid", MeshType::Pyramid, MeshPrimitiveInfo(0.50f, 5, 2.1f), Engine->Materials->GetMaterial("Box_mat"));
	Engine->CreateObject("Sphere", MeshType::Sphere, MeshPrimitiveInfo(0.50f, 12, true), Engine->Materials->GetMaterial("Box_mat"));
	Engine->CreateObject("Gun", modelsFolder + "gun.obj", Engine->Materials->GetMaterial("Box_mat"));
	SetLightedObject("Prism");
	SetLightedObject("Pyramid");
	SetLightedObject("Sphere");
	SetLightedObject("Gun");
}

void UpdateEachFrame() {

	if (Engine->InputManager->isKeyPressed_plus)
	{
		for (map<string, Object>::iterator objectIt : objectsParent)
		{
			objectIt->second.transform.Translate(0, 0, 0.03f);
		}
	}
	else if (Engine->InputManager->isKeyPressed_minus)
	{
		for (map<string, Object>::iterator objectIt : objectsParent)
		{
			objectIt->second.transform.Translate(0, 0, -0.03f);
		}
	}

	if (Engine->InputManager->isKeyPressed_E)
	{
		if (Engine->InputManager->isKeyPressed_W)
		{
			light_t->Translate(0, movementSpeed, 0);
		}

		if (Engine->InputManager->isKeyPressed_A)
		{
			light_t->Translate(-movementSpeed, 0, 0);
		}

		if (Engine->InputManager->isKeyPressed_S)
		{
			light_t->Translate(0, -movementSpeed, 0);
		}

		if (Engine->InputManager->isKeyPressed_D)
		{
			light_t->Translate(movementSpeed, 0, 0);
		}

		UpdateLightedObjectsShader();
	}
	else
	{
		for (map<string, Object>::iterator objectIt : objectsParent)
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
	}
}

void LateUpdateEachFrame(){

	txtRenderer->RenderText("This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
}

int main()
{
	Initialize();

	UpdateOnStart();

	Engine->StartGameLoop(UpdateEachFrame, LateUpdateEachFrame);

	//delete Engine;
	//delete txtRenderer;

	return 0;
}



#pragma region Car code

//float gasValue = 0.0f;
//Shader* rpm_shader;
//CarEngine* carEngine;

//initialize
//Engine->Materials->LoadShaders(vector<string>{ "background_shader", "rpm_shader", "car_shader", "light_shader", "diffuse_shader" });
//vector<string>{ "buffer_allocator.png", "dashboard_d.png", "box_d.jpg", "car_d.jpg", "rpm_d.png", "rpm_a.png"});

//carEngine = new CarEngine(900, 6800, 37 * updateRateFix, 30 * updateRateFix, 1500);

//update
//if (Engine->InputManager->isKeyPressed_E)
//{
//	carEngine->Throttle();
//}
//else
//{
//	carEngine->Idle();
//}

//car_t->Rotate(0.4 * updateRateFix,0,1,0);

//rpm_shader->setFloat("_gasValue", carEngine->GetNormalizedRPM());

#pragma endregion

