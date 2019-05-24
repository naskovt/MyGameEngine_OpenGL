#ifndef Materials_H
#define Materials_H

//#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Shader.h"
#include "Material.h"
#include "CoreStructures.h"


using namespace std;

class MaterialsManager
{
public:

	MaterialsManager();

	//void LoadShaders();

	void LoadTextures();

	void CreateMaterial(const string& name, Shader* shader);

	void CreateMaterial(const string& name, Shader* shader, vector<Texture>& textures);

	Material& GetMaterial(const string& name);

private:

	std::map< std::string, Material > _materials_map;


};

#endif

