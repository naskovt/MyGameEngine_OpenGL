#include "BasicModel.h"

//BasicModel::BasicModel(std::string text, const Material& mat) : ModelInterface(mat)
//{
//	switch (meshType)
//	{
//	case Triangle:
//		this->_mesh = new TriangleMesh();
//		break;
//	case Square:
//		this->_mesh = new SquareMesh();
//		break;
//	default:
//		std::cout << "\n ERROR - not implemented mesh type class !\n";
//		break;
//	}
//
//	this->LoadMeshToGPU();
//}

BasicModel::BasicModel(MeshType meshType, const Material& mat) : ModelInterface(mat)
{
	switch (meshType)
	{
	case Triangle:
		this->_mesh = new TriangleMesh();
		break;
	case Square:
		this->_mesh = new SquareMesh();
		break;
	default:
		std::cout << "\n ERROR - not implemented mesh type class !\n";
		break;
	}

	this->LoadMeshToGPU();
}

BasicModel::BasicModel(MeshType meshType, const MeshPrimitiveInfo& info, const Material& mat) : ModelInterface(mat)
{
	switch (meshType)
	{
	case Triangle:
		this->_mesh = new TriangleMesh();
		break;
	case Square:
		this->_mesh = new SquareMesh();
		break;
	case Prism:
		this->_mesh = new PrismMesh(info.sides, info.height, info.radius);
		break;
	case Sphere:
		this->_mesh = new SphereMesh(info.radius, info.sides, info.smooth);
		break;
	case Pyramid:
		this->_mesh = new PyramidMesh(info.sides, info.height, info.radius);
		break;
	default:
		std::cout << "\n ERROR - not implemented mesh type class !\n";
		break;
	}

	this->LoadMeshToGPU();
}


BasicModel::~BasicModel()
{
	//std::cout << "dtor called MODEL";

	delete this->_mesh;

	//// optional: de-allocate all resources once they've outlived their purpose:
	//// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void BasicModel::RenderModel() {

	this->material.GetShader().use();

	// set green - black timed color transition
	//float timeValue = glfwGetTime();
	//float timed_Value = (sin(timeValue) / 2.0f) + 0.5f;

	//this->material.GetShader().setFloat("timer", timed_Value);
	//this->material.GetShader().setVec4("color", this->material._color);


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, _mesh->indicesSize, GL_UNSIGNED_INT, 0);

	// no need to unbind it every time
	glBindVertexArray(0);
}

void BasicModel::LoadMeshToGPU() {

	//std::cout << std::endl;
	//std::cout << "vert size: " << _mesh->verticesSize;
	//std::cout << std::endl;
	//std::cout << "ind size: " << _mesh->indicesSize;
	//std::cout << std::endl;

	//size_t loaderIndex = 0;
	//for (size_t i = 0; i < _mesh->verticesSize ; i += 3)
	//{
	//	loaderIndex++;
	//	std::cout << "vert: " << loaderIndex << " : " << _mesh->vertices[i] << "  " << _mesh->vertices[i + 1] << "  " << _mesh->vertices[i + 2] << " \n";
	//}

	//loaderIndex = 0;
	//for (size_t i = 0; i < _mesh->indicesSize ; i += 3)
	//{
	//	loaderIndex++;
	//	std::cout << "ind: " << loaderIndex << " : " << _mesh->indices[i] << "  " << _mesh->indices[i + 1] << "  " << _mesh->indices[i + 2] << " \n";
	//}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _mesh->verticesSize * sizeof(float), _mesh->vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _mesh->indicesSize * sizeof(unsigned int), _mesh->indices, GL_DYNAMIC_DRAW);

	// layout index 0, 3 components(x,y,z), float data type, not normalized, stride(byte offset from each attribute), offset from the first attribute  
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEXOFFSET, nullptr); //  for position
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEXOFFSET, (void*)(3 * sizeof(float)) );	// for normals


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

