#include "MaterialsManager.h"



MaterialsManager::MaterialsManager() {

};

void MaterialsManager::LoadTextures(string path, vector<string> textureNames) {

	for (string name : textureNames)
	{
		this->LoadTexturesFromPath(path, name);
	}
}

void MaterialsManager::LoadShaders(vector<string> shadersNames) {


	///  Input names in order: vertex, fragment 
	for (string name : shadersNames)
	{
		this->_shaders_map.emplace(name, Shader( (ShadersFolder + name +  VertexShaderExtension).c_str() , (ShadersFolder + name + FragmentShaderExtension).c_str() ) );
	}
}


void MaterialsManager::CreateMaterial(const string& name, Shader* shader) {
	this->_materials_map.insert(make_pair(name, Material(*shader, 0, 0, 0, 1)));
}

void MaterialsManager::CreateMaterial(const string& name, const string shaderName) {

	this->_materials_map.insert(make_pair(name, Material(this->_shaders_map.find(shaderName)->second, 0, 0, 0, 1)));
}

void MaterialsManager::CreateMaterial(const string& name, const string shaderName, vector<string> texturesNames) {

	vector<Texture*> textures;

	for (string name : texturesNames)
	{
		textures.push_back(&this->_textures_map.find(name)->second);
	}

	this->_materials_map.insert(make_pair(name, Material(this->_shaders_map.find(shaderName)->second, textures)));
}


Material& MaterialsManager::GetMaterial(const string& name) {

	return this->_materials_map.find(name)->second;
}

unsigned int MaterialsManager::LoadTextureToGPU(string fullPath)
{
	int width, height, nrComponents;
	unsigned int textureID;

	glGenTextures(1, &textureID);

	unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = GL_RGBA;

		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;


		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}
	else
	{
		std::cout << "Texture failed to load at path: " << fullPath << std::endl;
	}

	stbi_image_free(data);

	return textureID;
}

Texture& MaterialsManager::LoadTexturesFromPath(const string path, const string name)
{
	Texture texture;
	texture.id = LoadTextureToGPU(path + "/" + name);
	texture.name = Helper::GetNameOnly(name);

	switch (texture.name[texture.name.size() - 1])
	{
	case 'n':
		texture.type = "_normal";
		break;
	case 'a':
		texture.type = "_alpha";
		break;
	case 's':
		texture.type = "_specular";
		break;
	default:
		texture.type = "_diffuse";
		break;
	}

	texture.path = path.c_str();
	this->_textures_map.insert(make_pair(name, texture));  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.

	return texture;
}