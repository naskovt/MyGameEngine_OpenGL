#include "GameEngine.h"


GameEngine::GameEngine(const unsigned int SCR_WIDTH_set, const unsigned int SCR_HEIGHT_set, const char* windowName,
															const char* vertShaderName, const char* fragShaderName)
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

	_customShaders = ShadersCreator(vertShaderName, fragShaderName);
};


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void GameEngine::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


void LoadTriangle2(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO) {

	//TODO not hardcoded mesh verticies and indecies !!

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		 0.10f,0.10f, 0.10f,  // top right
		 0.25f, -0.25f, 0.0f,  // bottom right
		-0.85f,  0.85f, 0.0f   // top left
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


}

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

void GameEngine::StartDrawingLoop() {

	// render loop
	// -----------

	while (!glfwWindowShouldClose(_window))
	{
		// input
		// -----
		processInput(_window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "timedColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// draw our gameobjects
		for (size_t i = 0; i < GameObjects_Vector.size(); i++)
		{
			// TODO make shader value for each object, in order to use different shaders for different objects
			GameObjects_Vector[i].UpdateDrawing(_customShaders);
		}



		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

}

GameEngine::~GameEngine()
{
	

	//// glfw: terminate, clearing all previously allocated GLFW resources.
	//// ------------------------------------------------------------------
	glfwTerminate();
	//std::cout << "\nengine d~tor..";
}

void GameEngine::AddObject(std::string name) {
	GameObjects_Vector.emplace_back(name);
}

