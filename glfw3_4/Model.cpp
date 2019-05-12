#include "Model.h"
#include "ResourcesObjLoader.h"



Model::Model(MeshType meshType, Material & material) : material(material)
{

	if (meshType == MeshType::Triangle)
	{
		this->_mesh = new TriangleMesh();

	}
	else if(meshType == MeshType::Square)
	{
		this->_mesh = new SquareMesh();
	}
	else
	{
		std::cout << "\n ERROR - not implemented mesh type class !\n";
	}

	this->LoadMeshToGPU();
}
Model::Model(std::string fileName, Material& material) : material(material), _mesh(new ResourcesObjLoader(fileName))
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

void Model::RenderModel() {

	this->material.GetShader().use();

	// set green - black timed color transition
	float timeValue = glfwGetTime();
	float timed_Value = (sin(timeValue) / 2.0f) + 0.5f;

	this->material.GetShader().setFloat("timer", timed_Value);
	this->material.GetShader().setVec4("color", this->material._color);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawElements(GL_TRIANGLES, 128, GL_UNSIGNED_INT, 0);
	
	// no need to unbind it every time
	glBindVertexArray(0);
}

void Model::LoadMeshToGPU() {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _mesh->verticesSize, _mesh->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _mesh->indicesSize, _mesh->indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}
