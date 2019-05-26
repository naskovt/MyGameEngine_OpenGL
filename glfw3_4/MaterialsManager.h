#ifndef Materials_H
#define Materials_H

//#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Shader.h"
#include "Material.h"
#include "CoreStructures.h"
#include "HelperFunctions.h"

#include "stb_image.h"
#include <assimp/scene.h>

using namespace std;

class MaterialsManager
{
public:

	MaterialsManager();


	void LoadTextures(string path, vector<string> textureNames);

	void LoadShaders(vector< pair<string, string> > shadersNames);

	void CreateMaterial(const string& name, Shader* shader);

	void CreateMaterial(const string& name, const string shaderName);

	void CreateMaterial(const string& name, const string shaderName, vector<string> texturesNames);
	

	Material& GetMaterial(const string& name);

private:

	std::map< std::string, Shader > _shaders_map;
	std::map< std::string, Texture > _textures_map;
	std::map< std::string, Material > _materials_map;

	unsigned int LoadTextureToGPU(string fullPath);

	Texture& LoadTexturesFromPath(const string path, const string name);

};

#endif

