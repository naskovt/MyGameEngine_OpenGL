#include "Enumerators.h"
#include "GameEngine.h"
#include "Constants.h"

GameEngine::GameEngine(const unsigned int SCR_WIDTH_set, const unsigned int SCR_HEIGHT_set, const char* windowName)
{

	// glfw: initialize and configure
	// ------------------------------
	if (!glfwInit())
	{
		std::cout << "GLFW failed to initialize" << std::endl;
	}

	_window = glfwCreateWindow(SCR_WIDTH_set, SCR_HEIGHT_set, windowName, NULL, NULL);


	if (_window == NULL)
	{
		std::cout << "\nctor = Failed to create GLFW window\n" << std::endl;
		glfwTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif

	if (!this->Initialize())
	{
		std::cerr << "ERROR INSIDE : Engine.Initialize()" << std::endl;
	}

	this->InputManager = new Input(_window);

	this->Materials = new MaterialsManager();

};

bool GameEngine::Initialize() {

	// glfw window creation
	// --------------------
	if (_window == NULL)
	{
		std::cout << "\nFailed to create GLFW window\n" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow * window, int width, int height) {glViewport(0, 0, width, height); });

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "\nFailed to initialize GLAD\n" << std::endl;
		return false;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// this will disable depth testing => //glDepthFunc(GL_ALWAYS); // always pass the depth test (same effect as glDisable(GL_DEPTH_TEST))


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return true;
}

void GameEngine::CreateObject(const std::string& name, MeshType meshType, Material& material) {
	GameObjects_Map.insert( make_pair(name, Object(meshType, material)) );
}

void GameEngine::CreateObject(const std::string& name, const std::string& fileName, Material& material) {
	GameObjects_Map.insert(make_pair(name, Object(fileName, material)));
}

void GameEngine::DrawGame() {

	// render fucntions

	// render
	// ------
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::map<std::string, Object>::iterator it = GameObjects_Map.begin();
	for (; it != GameObjects_Map.end() ; ++it)
	{
		it->second.UpdateDrawing();
	}

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void GameEngine::StartGameLoop(void (*UpdateGame)())
{
	while (!glfwWindowShouldClose(_window))
	{
		this->InputManager->Process();

		UpdateGame();

		DrawGame();
	}
}

map<string, Object>::iterator  GameEngine::GetObject_It(std::string name)
{
	return GameObjects_Map.find(name);
}

GameEngine::~GameEngine()
{

	//delete this->InputManager;
	//delete this->Materials;

	//// glfw: terminate, clearing all previously allocated GLFW resources.
	//// ------------------------------------------------------------------
	glfwTerminate();
	//std::cout << "\nengine d~tor..";
}

