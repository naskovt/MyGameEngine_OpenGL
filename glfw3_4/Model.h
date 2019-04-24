#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/glm.hpp>
#include "ShadersCreator.h"
#include <glfw3.h>


class Model
{
public:
	Model(Mesh mesh);
	~Model();

	virtual void RenderModel(ShadersCreator & shader);

private:
	
	void LoadMeshToGPU() {

		float vertices [9]{
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f,  0.5f, 0.0f   // top left
		};

		unsigned int indices [3]{  // note that we start from 0!
			0, 1, 2,  // first Triangle
		};


		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(_mesh.vertices), _mesh.vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_mesh.indices), _mesh.indices, GL_STATIC_DRAW);

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

	unsigned int VAO, VBO, EBO;

	Mesh _mesh;
};

#endif
