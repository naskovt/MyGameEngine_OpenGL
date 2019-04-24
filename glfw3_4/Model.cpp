#include "Model.h"



Model::Model(Mesh mesh) : _mesh(mesh)
{
	this->LoadMeshToGPU();
};


Model::~Model()
{
	//std::cout << "dtor called MODEL";

	//delete this->_mesh.vertices;
	//delete this->_mesh.indices;

	//// optional: de-allocate all resources once they've outlived their purpose:
	//// ------------------------------------------------------------------------
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
}

void Model::RenderModel(ShadersCreator & shader) {

	shader.use();

	// set green - black timed color transition
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	shader.setFloat("timedColor", greenValue);
	//


	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// glBindVertexArray(0); // no need to unbind it every time

	glBindVertexArray(0);
}
