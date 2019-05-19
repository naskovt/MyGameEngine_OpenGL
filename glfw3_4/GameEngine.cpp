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

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return true;
}

void GameEngine::CreateObject(const std::string& name, MeshType meshType, Material& material) {
	GameObjects_Map.insert( make_pair(name, Object(name, meshType, material)) );
}

void GameEngine::CreateObject(const std::string& name, const std::string& fileName, Material& material) {
	GameObjects_Map.insert(make_pair(name, Object(name, fileName, material)));
}

void GameEngine::DrawGame() {

	// render fucntions

	// render
	// ------
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

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

 Object& GameEngine::GetObjectByName(std::string name)
{
	 if (GameObjects_Map.find(name) == GameObjects_Map.end())
	 {
		 std::cout << " gameobject not found: " << name;
	 }

	return GameObjects_Map.find(name)->second;
}

GameEngine::~GameEngine()
{
	//// glfw: terminate, clearing all previously allocated GLFW resources.
	//// ------------------------------------------------------------------
	glfwTerminate();
	//std::cout << "\nengine d~tor..";
}

