#include "MaterialsManager.h"


MaterialsManager::MaterialsManager() {

};

void MaterialsManager::LoadTextures() {

}

void MaterialsManager::CreateMaterial(const string& name, Shader* shader) {
	this->_materials_map.insert(make_pair(name, Material(*shader, 0, 0, 0, 1)));
}

void MaterialsManager::CreateMaterial(const string& name, Shader* shader, vector<Texture>& textures) {
	//this->_materials_map.insert(make_pair(name, Material(shader, 0, 0, 0, 1)));

	// TODO Load textures in the material's object, not in Assimp'sMesh

}

Material& MaterialsManager::GetMaterial(const string& name) {

	return this->_materials_map.find(name)->second;
}