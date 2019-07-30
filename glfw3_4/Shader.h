#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "HelperFunctions.h"
#include "CoreStructures.h"

class Shader
{
public:

	unsigned int ID;
	const std::string name;
	bool isSeparateMVP = false;

	Shader() = default;
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec4(const std::string& name, float value[4]) const;
	void setVec3(const std::string& name, float value[3]) const;
	void setVec3(const std::string& name, Vector3 vec3) const;
	void setMatrix4(const std::string& name, glm::mat4 value) const;
	void setGlmVec3(const std::string& name, glm::vec3 vec3) const;
	void setInteger(const std::string& name, const int integer) const;
	
private:
	
	void checkCompileErrors(unsigned int shader, std::string type);

};
#endif