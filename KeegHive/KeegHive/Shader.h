#pragma once
#include <string>
#include <list>
#include "GL\glew.h"
#include <glm\glm\vec3.hpp>
#include <fstream>
class Shader
{
public:
	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
	~Shader();

	void setup();

	//Shader program and properties getters
	GLint getShaderID();
	GLint getModelMatrixLoc();
	GLint getViewMatrixLoc();
	GLint getProjectionMatrixLoc();

	//Filepaths
	std::string vertexPath;
	std::string fragmentPath;

	//Shader contents
	std::string vertexShader;
	std::string fragmentShader;

private:
	void loadShader();
	//Shader program ID
	GLint shaderID;

	//Uniform locations
	GLint modelMatrixLocation;
	GLint viewMatrixLocation;
	GLint projectionMatrixLocation;
};