#ifndef MODEL_ASSIMP_H
#define MODEL_ASSIMP_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "Shader.h"
#include "MeshAssimp.h"
#include "ModelInterface.h"
#include "Material.h"
#include "HelperFunctions.h"


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class ModelAssimp : public ModelInterface
{
public:
	/*  Model Data */
	//vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector<MeshAssimp> meshes;
	string directory;

	ModelAssimp(string const& path, const Material& material) : ModelInterface(material)
	{
		loadModel(path);
	}

	// draws the model, and thus all its meshes
	void RenderModel() override
	{

		for (unsigned int meshIndex = 0; meshIndex < meshes.size(); meshIndex++)
		{

			for (unsigned int textureIndex = 0; textureIndex < this->material._textures_v.size(); textureIndex++)
			{
				glActiveTexture(GL_TEXTURE0 + textureIndex); // active proper texture unit before binding

				string name = this->material._textures_v[textureIndex]->type ;

				//std::cout << " Shader ID: " << this->material.GetShader().ID  << "\n Tex name : "
				//	<< name  << " index : " << textureIndex << " id : " << this->material._textures_v[textureIndex]->id;

				// now set the sampler to the correct texture unit
				glUniform1i(glGetUniformLocation(this->material.GetShader().ID, name.c_str()), textureIndex);
				// and finally bind the texture
				glBindTexture(GL_TEXTURE_2D, this->material._textures_v[textureIndex]->id);
			}

			// draw mesh
			glBindVertexArray(meshes[meshIndex].VAO);
			glDrawElements(GL_TRIANGLES, meshes[meshIndex].indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// always good practice to set everything back to defaults once configured.
			glActiveTexture(GL_TEXTURE0);

		}
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);

	}

private:

	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(string const& path)
	{
		// read file via ASSIMP
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		// check for errors
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
			return;
		}
		// retrieve the directory path of the filepath
		directory = path.substr(0, path.find_last_of('/'));

		// process ASSIMP's root node recursively
		processNode(scene->mRootNode, scene);
	}

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode * node, const aiScene * scene)
	{
		// process each mesh located at the current node
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			// the node object only contains indices to index the actual objects in the scene. 
			// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}
		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}

	}

	MeshAssimp processMesh(aiMesh * mesh, const aiScene * scene)
	{
		// data to fill
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		//vector<Texture> textures;

		// Walk through each of the mesh's vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
			// positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
			// normals
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
			// texture coordinates
			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);


				///////////////////// Tangents and bitangents currently disabled /////////////// MOD CUSTOM

			// tangent
			//vector.x = mesh->mTangents[i].x;
			//vector.y = mesh->mTangents[i].y;
			//vector.z = mesh->mTangents[i].z;
			//vertex.Tangent = vector;
			//// bitangent
			//vector.x = mesh->mBitangents[i].x;
			//vector.y = mesh->mBitangents[i].y;
			//vector.z = mesh->mBitangents[i].z;
			//vertex.Bitangent = vector;
			vertices.push_back(vertex);
		}
		// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		// return a mesh object created from the extracted mesh data
		return MeshAssimp(vertices, indices);
	}

};




#endif // MODEL_ASSIMP_H