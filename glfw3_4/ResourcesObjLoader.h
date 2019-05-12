#pragma once
#include "ObjLoader/cObj.h"
#include "Mesh.h"

class ResourcesObjLoader : public Mesh {

public:

	ResourcesObjLoader(std::string filePath) {

		
		Loader = cObj(filePath);

		size_t vertices_Size = Loader.vertices.size() * 3;
		this->vertices = new float[vertices_Size];

		size_t loaderIndex = 0;
		for (size_t i = 0; i < vertices_Size; i+=3 )
		{
			this->vertices[i] = Loader.vertices[loaderIndex].v[0];
			this->vertices[i + 1] = Loader.vertices[loaderIndex].v[1];
			this->vertices[i + 2] = Loader.vertices[loaderIndex].v[2];
			loaderIndex++;
			std::cout << "vert: "<< loaderIndex << " : " << this->vertices[i] << " _ " << this->vertices[i+1] << " _ " << this->vertices[i+2] << " \n";
		}


		size_t indices_Size = Loader.faces.size() * 3;
		this->indices = new unsigned int[indices_Size];

		loaderIndex = 0;
		for (size_t i = 0; i < indices_Size; i += 3)
		{
			this->indices[i] = Loader.faces[loaderIndex].vertex[0];
			this->indices[i + 1] = Loader.faces[loaderIndex].vertex[1];
			this->indices[i + 2] = Loader.faces[loaderIndex].vertex[2];
			loaderIndex++;
			std::cout << "ind: " << loaderIndex << " : " << this->indices[i] << " _ " << this->indices[i+1] << " _ " << this->indices[i+2] << " \n";
		}


		this->verticesSize = Loader.vertices.size() * 4;
		this->indicesSize = Loader.faces.size() * 3;
	}
private:

	cObj Loader;

	void PrintMeshesInfo(bool loadout) {

		if (loadout)
		{

				
		}
		// If not output an error
		else
		{
			// Create/Open e1Out.txt
			std::ofstream file("e1Out.txt");

			// Output Error
			std::cout << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";
			file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";

			// Close File
			file.close();
		}
	}
};