#ifndef INPUT_H
#define INPUT_H


class Input
{
public:

	bool isKeyPressed_E;
	bool isKeyPressed_W;
	bool isKeyPressed_A;
	bool isKeyPressed_S;
	bool isKeyPressed_D;
	bool isKeyPressed_ESC;

	Input() = delete;

	Input(GLFWwindow* window) : isKeyPressed_W(false),
		isKeyPressed_A(false),
		isKeyPressed_S(false),
		isKeyPressed_D(false),
		isKeyPressed_E(false),
		isKeyPressed_ESC(false),
		_window(window)
	{


	};


	void Process() {


		UpdateKeyDown(GLFW_KEY_ESCAPE, isKeyPressed_ESC);
		UpdateKeyDown(GLFW_KEY_E, isKeyPressed_E);
		UpdateKeyDown(GLFW_KEY_W, isKeyPressed_W);
		UpdateKeyDown(GLFW_KEY_A, isKeyPressed_A);
		UpdateKeyDown(GLFW_KEY_S, isKeyPressed_S);
		UpdateKeyDown(GLFW_KEY_D, isKeyPressed_D);
	}



private:

	GLFWwindow* _window;

	//GLFWkeyfun keyCallback_g;

	//void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	//}

	void UpdateKeyDown(int key, bool& variableKeyToSet) {

		if (glfwGetKey(_window, key) == GLFW_PRESS) {
			variableKeyToSet = true;
		}
		else if (false != variableKeyToSet)
		{
			variableKeyToSet = false;
		}
	}

};

#endif
